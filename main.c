#include <atmel_start.h>
#include "driver_init.h"

//#define EDBG_TEST
#define CAMERA_0_TEST

#define CAMERA_OV7670_RESOLUTION		(320*240)
#define OV7670_SLAVE_ADDRESS			0x21
#define OV7670_CHIPID_HIGH 				0x0A
#define OV7670_CHIPID_LOW 				0x0B
#define OV7670_CHIPID_VID 				0x76
#define OV7670_CHIPID_PID 				0x73

#ifdef EDBG_TEST
static uint8_t Display_title[]				= "**************** PCC CAMERA INTERFACE EXAMPLE - OV7670 ****************\r\n";
#endif

#ifdef CAMERA_0_TEST
static uint8_t Display_Valid_VID_PID[]		= "VID / PID read successful !!!\r\n";
static uint8_t Display_Invalid_VID_PID[]	= "VID / PID Invalid !!!\r\n";
#endif

static union data
{
	uint16_t hword[CAMERA_OV7670_RESOLUTION]; // 76800
	uint8_t byte[CAMERA_OV7670_RESOLUTION * 2];  // 76800 * 2
	
}CAMERA_OV7670_frame_buf;

static uint32_t Index;

uint32_t flag_frame_captured = 0;
struct io_descriptor *PCC_SCCB_io;


uint8_t flag_teste;

//uint8_t sync_britto=0;

void pcc_write_reg (uint8_t addr, uint8_t dat)
{
	uint8_t PCC_SCCB_Buffer[2];
	PCC_SCCB_Buffer[0] = addr;
	PCC_SCCB_Buffer[1] = dat;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
}

static void ext_irq_cb_PCC_VSYNC(void)
{
	
	//Do Nothing
//	asm ("nop");
}

void config_sensor_ov7670(void)
{

	uint8_t PCC_SCCB_Buffer[2];
	uint8_t recv_vid;
	uint8_t recv_pid;
	
	gpio_set_pin_level(PCC_PWDN, false);
	gpio_set_pin_level(PCC_RESET, true);
	delay_ms(10);
	
	i2c_m_sync_get_io_descriptor(&PCC_SCCB, &PCC_SCCB_io);
	i2c_m_sync_enable(&PCC_SCCB);
	i2c_m_sync_set_slaveaddr(&PCC_SCCB, OV7670_SLAVE_ADDRESS, I2C_M_SEVEN);

	PCC_SCCB_Buffer[0] = OV7670_CHIPID_HIGH;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 1);
	io_read(&PCC_SCCB.io, &recv_vid, 1);

	delay_ms(10);
	PCC_SCCB_Buffer[0] = OV7670_CHIPID_LOW;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 1);
	io_read(&PCC_SCCB.io, &recv_pid, 1);
	delay_ms(10);
	if(OV7670_CHIPID_VID == recv_vid && OV7670_CHIPID_PID == recv_pid)
	{
		#ifdef CAMERA_0_TEST
		io_write(&EDBG_COM.io, Display_Valid_VID_PID, sizeof(Display_Valid_VID_PID));
		#endif
	}
	else
	{
		#ifdef CAMERA_0_TEST
		io_write(&EDBG_COM.io, Display_Invalid_VID_PID, sizeof(Display_Invalid_VID_PID));
		#endif
		while(1);
	}
	
	PCC_SCCB_Buffer[0] = 0x0C;
	PCC_SCCB_Buffer[1] = 0x08;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x12;
	PCC_SCCB_Buffer[1] = 0x14;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x15;
	PCC_SCCB_Buffer[1] = 0x02;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x40;
	PCC_SCCB_Buffer[1] = 0xD0;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x1E;
	PCC_SCCB_Buffer[1] = 0x31;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x3A;
	PCC_SCCB_Buffer[1] = 0x0C;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x3E;
	PCC_SCCB_Buffer[1] = 0x19;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x73;
	PCC_SCCB_Buffer[1] = 0xF1;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x17;
	PCC_SCCB_Buffer[1] = 0x0B;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x32;
	PCC_SCCB_Buffer[1] = 0x80;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);

	
}

int main(void)
{
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	usart_async_enable(&EDBG_COM);
	
 	pwm_set_parameters(&PWM_0, 4,2);
 
 	pwm_enable(&PWM_0);		
	
#ifdef EDBG_TEST
	while(1)
	{
		for(Index = 0; Index < sizeof(Display_title); Index++)
		{
			while(_usart_async_is_byte_sent(&EDBG_COM.device) == 0);
			_usart_async_write_byte(&EDBG_COM.device, Display_title[Index]);
		}
	}
#endif
		memset(CAMERA_OV7670_frame_buf.hword,0x30,sizeof(CAMERA_OV7670_frame_buf.hword));
  		config_sensor_ov7670();
		ext_irq_register(PCC_VSYNC, ext_irq_cb_PCC_VSYNC);
  		
 		while(gpio_get_pin_level(PCC_VSYNC) == 0);
 		while(gpio_get_pin_level(PCC_VSYNC) != 0);
 		camera_async_enable(&CAMERA_OV7670);
 		camera_async_capture_start(&CAMERA_OV7670, 0, (uint32_t *) &CAMERA_OV7670_frame_buf.hword[0]);

		
 		flag_frame_captured = 0;
 		while(flag_frame_captured == 0);
 		camera_async_disable(&CAMERA_OV7670);
 		ext_irq_disable(PCC_VSYNC);
//	    memset(CAMERA_OV7670_frame_buf.hword,0x30,sizeof(CAMERA_OV7670_frame_buf.hword));
		for(Index = 0; Index < 153600; Index++)		
		{
			while(_usart_async_is_byte_sent(&EDBG_COM.device) == 0);
			_usart_async_write_byte(&EDBG_COM.device, CAMERA_OV7670_frame_buf.byte[Index]);
			delay_us(10);
		}
		
		while (1);
}
