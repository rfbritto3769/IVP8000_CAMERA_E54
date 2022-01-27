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

uint32_t Index;

uint32_t flag_frame_captured = 0;
struct io_descriptor *PCC_SCCB_io;


uint8_t flag_teste;

void pcc_write_reg (uint8_t addr, uint8_t dat)
{
	uint8_t PCC_SCCB_Buffer[2];
	PCC_SCCB_Buffer[0] = addr;
	PCC_SCCB_Buffer[1] = dat;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	//delay_ms(1);
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
	
// 	    pcc_write_reg(0x17,0x13);
// 		pcc_write_reg(0x17,0x0b);
// 		pcc_write_reg(0x40,0xd0);
// 		pcc_write_reg(0x3a,0x0c);
// 		pcc_write_reg(0x12,0x14);
// 		pcc_write_reg(0x18,0x01);
// 		pcc_write_reg(0x32,0x6b);
// 		pcc_write_reg(0x32,0x80);
// 		pcc_write_reg(0x19,0x02);
// 		pcc_write_reg(0x1a,0x7a);
// 		pcc_write_reg(0x03,0x0a);
// 		pcc_write_reg(0x0c,0x00);
// 		pcc_write_reg(0x0c,0x08);
// 		pcc_write_reg(0x3e,0x00);
// 		pcc_write_reg(0x3e,0x19);
// 		/* Mystery scaling numbers */
// 	 	pcc_write_reg(0x70, 0x3a);
// 	 	pcc_write_reg(0x71, 0x35);
// 	 	pcc_write_reg(0x72, 0x11);
// 	 	pcc_write_reg(0x73, 0xF1);
// 	 	pcc_write_reg(0xa2, 0x01);
// 	 	pcc_write_reg(0x15, 0x00);
// 		pcc_write_reg(0x15, 0x02);
// 		 /* Gamma curve values */
// 		pcc_write_reg(0x7a, 0x20);
// 		pcc_write_reg(0x7b, 0x10);
// 		pcc_write_reg(0x7c, 0x1e);
// 		pcc_write_reg(0x7d, 0x35);
// 		pcc_write_reg(0x7e, 0x5a);
// 		pcc_write_reg(0x7f, 0x69);
// 		pcc_write_reg(0x80, 0x76);
// 		pcc_write_reg(0x81, 0x80);
// 		pcc_write_reg(0x82, 0x88);
// 		pcc_write_reg(0x83, 0x8f);
// 		pcc_write_reg(0x84, 0x96);
// 		pcc_write_reg(0x85, 0xa3);
// 		pcc_write_reg(0x86, 0xaf);
// 		pcc_write_reg(0x87, 0xc4);
// 		pcc_write_reg(0x88, 0xd7);
// 		pcc_write_reg(0x89, 0xe8);
// 		  /* AGC and AEC parameters.  Note we start by disabling those features,
// 		 then turn them only after tweaking the values. */
// 		pcc_write_reg(0x13, 0xc0);
// 		pcc_write_reg(0x00, 0x00);
// 		pcc_write_reg(0x10, 0x00);
// 		pcc_write_reg(0x0D, 0x40);	/* magic reserved bit */
// 		pcc_write_reg(0x14, 0x18);	/* 4x gain + magic rsvd bit */
// 		pcc_write_reg(0xa5, 0x05);
// 		pcc_write_reg(0xab, 0x07);
// 		pcc_write_reg(0x24, 0x95);
// 		pcc_write_reg(0x25, 0x33);
// 		pcc_write_reg(0x26, 0xe3);
// 		pcc_write_reg(0x9f, 0x78);
// 		pcc_write_reg(0xa0, 0x68);
// 		pcc_write_reg(0xa1, 0x03); /* magic */
// 		pcc_write_reg(0xa6, 0xd8);
// 		pcc_write_reg(0xa7, 0xd8);
// 		pcc_write_reg(0xa8, 0xf0);
// 		pcc_write_reg(0xa9, 0x90);
// 		pcc_write_reg(0xaa, 0x94);
// 		pcc_write_reg(0x13, 0xc5);
// 		pcc_write_reg(0x30, 0x00);
// 		pcc_write_reg(0x31, 0x00); //disable some delays
// 		/* Almost all of these are magic "reserved" values.  */
// 		pcc_write_reg(0x0e, 0x61);
// 		pcc_write_reg(0x0f, 0x4b);
// 		pcc_write_reg(0x16, 0x02);
// 		pcc_write_reg(0x1e, 0x07);
// 		pcc_write_reg(0x1e, 0x31);
// 		pcc_write_reg(0x21, 0x02);
// 		pcc_write_reg(0x22, 0x91);
// 		pcc_write_reg(0x29, 0x07);
// 		pcc_write_reg(0x33, 0x0b);
// 		pcc_write_reg(0x35, 0x0b);
// 		pcc_write_reg(0x37, 0x1d);
// 		pcc_write_reg(0x38, 0x71);
// 		pcc_write_reg(0x39, 0x2a);
// 		pcc_write_reg(0x3c, 0x78);
// 		pcc_write_reg(0x4d, 0x40);
// 		pcc_write_reg(0x4e, 0x20);
// 		pcc_write_reg(0x69, 0x00);
// 		pcc_write_reg(0x74, 0x10);
// 		pcc_write_reg(0x8d, 0x4f);
// 		pcc_write_reg(0x8e, 0x00);
// 		pcc_write_reg(0x8f, 0x00);
// 		pcc_write_reg(0x90, 0x00);
// 		pcc_write_reg(0x91, 0x00);
// 		pcc_write_reg(0x96, 0x00);
// 		pcc_write_reg(0x9a, 0x00);
// 		pcc_write_reg(0xb0, 0x84);
// 		pcc_write_reg(0xb1, 0x0c);
// 		pcc_write_reg(0xb2, 0x0e);
// 		pcc_write_reg(0xb3, 0x82);
// 		pcc_write_reg(0xb8, 0x0a);
// 		 /* More reserved magic, some of which tweaks white balance */
// 		pcc_write_reg(0x43, 0x0a);
// 		pcc_write_reg(0x44, 0xf0);
// 		pcc_write_reg(0x45, 0x34);
// 		pcc_write_reg(0x46, 0x58);
// 		pcc_write_reg(0x47, 0x28);
// 		pcc_write_reg(0x48, 0x3a);
// 		pcc_write_reg(0x59, 0x88);
// 		pcc_write_reg(0x5a, 0x88);
// 		pcc_write_reg(0x5b, 0x44);
// 		pcc_write_reg(0x5c, 0x67);
// 		pcc_write_reg(0x5d, 0x49);
// 		pcc_write_reg(0x5e, 0x0e);
// 		pcc_write_reg(0x6c, 0x0a);
// 		pcc_write_reg(0x6d, 0x55);
// 		pcc_write_reg(0x6e, 0x11);
// 		pcc_write_reg(0x6f, 0x9e);
// 		pcc_write_reg(0x6a, 0x40);
// 		pcc_write_reg(0x01, 0x40);
// 		pcc_write_reg(0x02, 0x60);
// 		pcc_write_reg(0x13, 0xc7);
// 		/* Matrix coefficients */
// 		pcc_write_reg(0x4f, 0x80 );
// 		pcc_write_reg(0x50, 0x80);
// 		pcc_write_reg(0x51, 0x00);
// 		pcc_write_reg(0x52, 0x22);
// 		pcc_write_reg(0x53, 0x5e);
// 		pcc_write_reg(0x54, 0x80);
// 		pcc_write_reg(0x58, 0x9e);
// 		pcc_write_reg(0x41, 0x08);
// 		pcc_write_reg(0x3f, 0x00);
// 		pcc_write_reg(0x75, 0x05);
// 		pcc_write_reg(0x76, 0xe1);
// 		pcc_write_reg(0x4c, 0);
// 		pcc_write_reg(0x77, 0x01);
// 		pcc_write_reg(0x3d, 0x48);
// 		pcc_write_reg(0x4b, 0x09);
// 		pcc_write_reg(0xc9, 0x60);
// 		pcc_write_reg(0x56, 0x40);
// 		pcc_write_reg(0x34, 0x11);
// 		pcc_write_reg(0x3b, 0x12);
// 		pcc_write_reg(0xa4, 0x82);
// 		pcc_write_reg(0x96, 0);
// 		pcc_write_reg(0x97, 0x30 );
// 		pcc_write_reg(0x98, 0x20);
// 		pcc_write_reg(0x99, 0x30);
// 		pcc_write_reg(0x9a, 0x84 );
// 		pcc_write_reg( 0x9b, 0x29 );
// 		pcc_write_reg(0x9c, 0x03);
// 		pcc_write_reg( 0x9d, 0x4c );
// 		pcc_write_reg( 0x9e, 0x3f );
// 		pcc_write_reg(0x78, 0x04 );
// 		 /* Extra-weird stuff.  Some sort of multiplexor register */
// 		pcc_write_reg(0x79, 0x01);
// 		pcc_write_reg(0xc8, 0xf0);
// 		pcc_write_reg(0x79, 0x0f);
// 		pcc_write_reg(0xc8, 0x00);
// 		pcc_write_reg(0x79, 0x10);
// 		pcc_write_reg(0xc8, 0x7e);
// 		pcc_write_reg(0x79, 0x0a);
// 		pcc_write_reg(0xc8, 0x80);
// 		pcc_write_reg(0x79, 0x0b);
// 		pcc_write_reg(0xc8, 0x01);
// 		pcc_write_reg(0x79, 0x0c);
// 		pcc_write_reg(0xc8, 0x0f);
// 		pcc_write_reg(0x79, 0x0d);
// 		pcc_write_reg(0xc8, 0x20);
// 		pcc_write_reg(0x79, 0x09);
// 		pcc_write_reg(0xc8, 0x80);
// 		pcc_write_reg(0x79, 0x02);
// 		pcc_write_reg(0xc8, 0xc0);
// 		pcc_write_reg(0x79, 0x03);
// 		pcc_write_reg(0xc8, 0x40);
// 		pcc_write_reg(0x79, 0x05);
// 		pcc_write_reg(0xc8, 0x30);
// 		pcc_write_reg(0x79, 0x26);
// 		pcc_write_reg(0xff, 0xff);
// 
// 	PCC_SCCB_Buffer[0] = 0x12;
// 	PCC_SCCB_Buffer[1] = 0x80;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
// 	delay_ms(100);
// 	
// 	PCC_SCCB_Buffer[0] = 0x73;
// 	PCC_SCCB_Buffer[1] = 0xF4;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x3a;
// 	PCC_SCCB_Buffer[1] = 0x04;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x12;
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x15;
// 	PCC_SCCB_Buffer[1] = 0x20;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	
// 	PCC_SCCB_Buffer[0] = 0x03;
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 		
// 	PCC_SCCB_Buffer[0] = 0x32;
// 	PCC_SCCB_Buffer[1] = 0xf6;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x17;
// 	PCC_SCCB_Buffer[1] = 0x13;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x18;
// 	PCC_SCCB_Buffer[1] = 0x01;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x19;
// 	PCC_SCCB_Buffer[1] = 0x02;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x1a;
// 	PCC_SCCB_Buffer[1] = 0x7a;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x03;
// 	PCC_SCCB_Buffer[1] = 0x0a;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0xff;
// 	PCC_SCCB_Buffer[1] = 0xff;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	
// 	
// 	PCC_SCCB_Buffer[0] = 0x12;
// 	PCC_SCCB_Buffer[1] = 0x01;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x3d;
// 	PCC_SCCB_Buffer[1] = 0x08;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x41;
// 	PCC_SCCB_Buffer[1] = 0x3d;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x76;
// 	PCC_SCCB_Buffer[1] = 0xe1;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0xff;
// 	PCC_SCCB_Buffer[1] = 0xff;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x11;
// 	PCC_SCCB_Buffer[1] = 0x25;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	///////////////////////////////////////////////////
	
	PCC_SCCB_Buffer[0] = 0x0C;
	PCC_SCCB_Buffer[1] = 0x07;//08
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x12;
	PCC_SCCB_Buffer[1] = 0x14;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x15;
	PCC_SCCB_Buffer[1] = 0x03;//02
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x40;
	PCC_SCCB_Buffer[1] = 0xD0;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x1E;
	PCC_SCCB_Buffer[1] = 0x01;//31
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x3A;
	PCC_SCCB_Buffer[1] = 0x0C;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x3E;
	PCC_SCCB_Buffer[1] = 0x19; //19
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
// 	PCC_SCCB_Buffer[0] = 0x73;
// 	PCC_SCCB_Buffer[1] = 0xF1;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);

	PCC_SCCB_Buffer[0] = 0x73;
	PCC_SCCB_Buffer[1] = 0xF2;
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
// 	PCC_SCCB_Buffer[0] = 0x72;// novo
// 	PCC_SCCB_Buffer[1] = 0x11;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x18; //novo
// 	PCC_SCCB_Buffer[1] = 0x01;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x19; // novo
// 	PCC_SCCB_Buffer[1] = 0x02;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x1a; //novo
// 	PCC_SCCB_Buffer[1] = 0x7a;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 		
// 	PCC_SCCB_Buffer[0] = 0x03; //novo
// 	PCC_SCCB_Buffer[1] = 0x0a;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
// 	PCC_SCCB_Buffer[0] = 0x12; //novo
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x8c; //novo
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x04; //novo
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x40; //novo
// 	PCC_SCCB_Buffer[1] = 0xc0;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x14; //novo
// 	PCC_SCCB_Buffer[1] = 0x6a;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x4f; //novo
// 	PCC_SCCB_Buffer[1] = 0x80;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x50; //novo
// 	PCC_SCCB_Buffer[1] = 0x80;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x51; //novo
// 	PCC_SCCB_Buffer[1] = 0x00;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x52; //novo
// 	PCC_SCCB_Buffer[1] = 0x22;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x53; //novo
// 	PCC_SCCB_Buffer[1] = 0x5e;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x54; //novo
// 	PCC_SCCB_Buffer[1] = 0x80;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
// 	
// 	PCC_SCCB_Buffer[0] = 0x3d; //novo
// 	PCC_SCCB_Buffer[1] = 0x40;
// 	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
		
	PCC_SCCB_Buffer[0] = 0x17;
	PCC_SCCB_Buffer[1] = 0x16;//0x0b  16
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);
	
	PCC_SCCB_Buffer[0] = 0x32;
	PCC_SCCB_Buffer[1] = 0x24;//80
	io_write(&PCC_SCCB.io, PCC_SCCB_Buffer, 2);

	
}

int main(void)
{
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	gpio_set_pin_level(PCC_RESET, false);
	usart_async_enable(&EDBG_COM);
	
 	pwm_set_parameters(&PWM_0,22,11);
 
 	pwm_enable(&PWM_0);	
	
	
// #ifdef EDBG_TEST
// 	while(1)
// 	{
// 		for(Index = 0; Index < sizeof(Display_title); Index++)
// 		{
// 			while(_usart_async_is_byte_sent(&EDBG_COM.device) == 0);
// 			_usart_async_write_byte(&EDBG_COM.device, Display_title[Index]);
// 		}
// 	}
// #endif
		memset(CAMERA_OV7670_frame_buf.hword,0x30,sizeof(CAMERA_OV7670_frame_buf.hword));
     	config_sensor_ov7670();
 		ext_irq_register(PCC_VSYNC, ext_irq_cb_PCC_VSYNC);
   		
 		while(gpio_get_pin_level(PCC_VSYNC) == 0);
 		while(gpio_get_pin_level(PCC_VSYNC) != 0);
  		camera_async_enable(&CAMERA_OV7670);
  		camera_async_capture_start(&CAMERA_OV7670, 0, (uint32_t *) &CAMERA_OV7670_frame_buf.hword[0]);
//  
		
 		flag_frame_captured = 0;
 		while(flag_frame_captured == 0);
		camera_async_disable(&CAMERA_OV7670);
 		ext_irq_disable(PCC_VSYNC);
	  //  memset(CAMERA_OV7670_frame_buf.hword,0x30,sizeof(CAMERA_OV7670_frame_buf.hword));
		for(Index = 0; Index < 153600; Index++)		
		{
			while(_usart_async_is_byte_sent(&EDBG_COM.device) == 0);
			_usart_async_write_byte(&EDBG_COM.device, CAMERA_OV7670_frame_buf.byte[Index]);
			delay_us(10);
		}
		
		while (1);
}
