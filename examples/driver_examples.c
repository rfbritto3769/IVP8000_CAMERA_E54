/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static void button_on_PA12_pressed(void)
{
}

static void button_on_PA13_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PA12, button_on_PA12_pressed);
	ext_irq_register(PIN_PA13, button_on_PA13_pressed);
}

/**
 * It's just demo for usage and assume that
 * the frame size is very small, in actually application,
 * the frame size  should be big enough for a frame.
 */
uint32_t frame_buf[CONF_PCC_DMA_FRAME_SIZE];

/**
 * Example of using CAMERA_OV7670.
 */

static void capture_cb(struct camera_async_descriptor *const descr, uint32_t ch)
{
	if (ch == 0) {
		// Application can process data in frame_buf.
		camera_async_capture_start(&CAMERA_OV7670, 0, frame_buf);
	}
}
/**
 * Application example.
 */
void CAMERA_OV7670_example(void)
{
	camera_async_register_callback(&CAMERA_OV7670, capture_cb);
	camera_async_enable(&CAMERA_OV7670);
	camera_async_capture_start(&CAMERA_OV7670, 0, frame_buf);
}

/**
 * Example of using EDBG_COM to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_EDBG_COM[12] = "Hello World!";

static void tx_cb_EDBG_COM(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void EDBG_COM_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&EDBG_COM, USART_ASYNC_TXC_CB, tx_cb_EDBG_COM);
	/*usart_async_register_callback(&EDBG_COM, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&EDBG_COM, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&EDBG_COM, &io);
	usart_async_enable(&EDBG_COM);

	io_write(io, example_EDBG_COM, 12);
}

void PCC_SCCB_example(void)
{
	struct io_descriptor *PCC_SCCB_io;

	i2c_m_sync_get_io_descriptor(&PCC_SCCB, &PCC_SCCB_io);
	i2c_m_sync_enable(&PCC_SCCB);
	i2c_m_sync_set_slaveaddr(&PCC_SCCB, 0x12, I2C_M_SEVEN);
	io_write(PCC_SCCB_io, (uint8_t *)"Hello World!", 12);
}

void delay_example(void)
{
	delay_ms(5000);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}
