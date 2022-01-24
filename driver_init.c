/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

/*! The buffer size for USART */
#define EDBG_COM_BUFFER_SIZE 16

struct usart_async_descriptor EDBG_COM;

static uint8_t EDBG_COM_buffer[EDBG_COM_BUFFER_SIZE];

struct camera_async_descriptor CAMERA_OV7670;

struct i2c_m_sync_desc PCC_SCCB;

struct pwm_descriptor PWM_0;

void EXTERNAL_IRQ_0_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, EIC_GCLK_ID, CONF_GCLK_EIC_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBAMASK_EIC_bit(MCLK);

	// Set pin direction to input
	gpio_set_pin_direction(PCC_VSYNC, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PCC_VSYNC,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PCC_VSYNC, PINMUX_PA12A_EIC_EXTINT12);

	// Set pin direction to input
	gpio_set_pin_direction(PCC_HSYNC, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PCC_HSYNC,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PCC_HSYNC, PINMUX_PA13A_EIC_EXTINT13);

	ext_irq_init();
}

void EVENT_SYSTEM_0_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, EVSYS_GCLK_ID_1, CONF_GCLK_EVSYS_CHANNEL_1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBBMASK_EVSYS_bit(MCLK);

	event_system_init();
}

void CAMERA_OV7670_PORT_init(void)
{

	gpio_set_pin_function(PCC_PCLK, PINMUX_PA14K_PCC_CLK);

	gpio_set_pin_function(PCC_DATA0, PINMUX_PA16K_PCC_DATA0);

	gpio_set_pin_function(PCC_DATA1, PINMUX_PA17K_PCC_DATA1);

	gpio_set_pin_function(PCC_DATA2, PINMUX_PA18K_PCC_DATA2);

	gpio_set_pin_function(PCC_DATA3, PINMUX_PA19K_PCC_DATA3);

	gpio_set_pin_function(PCC_DATA4, PINMUX_PA20K_PCC_DATA4);

	gpio_set_pin_function(PCC_DATA5, PINMUX_PA21K_PCC_DATA5);

	gpio_set_pin_function(PCC_DATA6, PINMUX_PA22K_PCC_DATA6);

	gpio_set_pin_function(PCC_DATA7, PINMUX_PA23K_PCC_DATA7);
}

void CAMERA_OV7670_CLOCK_init(void)
{
	hri_mclk_set_APBDMASK_PCC_bit(MCLK);
}

void CAMERA_OV7670_init(void)
{
	CAMERA_OV7670_CLOCK_init();
	camera_async_init(&CAMERA_OV7670, PCC);
	CAMERA_OV7670_PORT_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void EDBG_COM_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBAMASK_SERCOM1_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void EDBG_COM_PORT_init()
{

	gpio_set_pin_function(PC27, PINMUX_PC27C_SERCOM1_PAD0);

	gpio_set_pin_function(PC28, PINMUX_PC28C_SERCOM1_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void EDBG_COM_init(void)
{
	EDBG_COM_CLOCK_init();
	usart_async_init(&EDBG_COM, SERCOM1, EDBG_COM_buffer, EDBG_COM_BUFFER_SIZE, (void *)NULL);
	EDBG_COM_PORT_init();
}

void PCC_SCCB_PORT_init(void)
{

	gpio_set_pin_pull_mode(PCC_SCCB_SDA,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PCC_SCCB_SDA, PINMUX_PD08C_SERCOM7_PAD0);

	gpio_set_pin_pull_mode(PCC_SCCB_SCL,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PCC_SCCB_SCL, PINMUX_PD09C_SERCOM7_PAD1);
}

void PCC_SCCB_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM7_GCLK_ID_CORE, CONF_GCLK_SERCOM7_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM7_GCLK_ID_SLOW, CONF_GCLK_SERCOM7_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBDMASK_SERCOM7_bit(MCLK);
}

void PCC_SCCB_init(void)
{
	PCC_SCCB_CLOCK_init();
	i2c_m_sync_init(&PCC_SCCB, SERCOM7);
	PCC_SCCB_PORT_init();
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void PWM_0_PORT_init(void)
{

	gpio_set_pin_function(PD11, PINMUX_PD11F_TCC0_WO4);
}

void PWM_0_CLOCK_init(void)
{

	hri_mclk_set_APBBMASK_TCC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TCC0_GCLK_ID, CONF_GCLK_TCC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void PWM_0_init(void)
{
	PWM_0_CLOCK_init();
	PWM_0_PORT_init();
	pwm_init(&PWM_0, TCC0, _tcc_get_pwm());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PC11

	gpio_set_pin_level(PC11,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PC11, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PC11, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC12

	gpio_set_pin_level(PC12,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PC12, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PC12, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC22

	gpio_set_pin_level(PCC_PWDN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(PCC_PWDN, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PCC_PWDN, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC23

	gpio_set_pin_level(PCC_RESET,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	// Set pin direction to output
	gpio_set_pin_direction(PCC_RESET, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(PCC_RESET, GPIO_PIN_FUNCTION_OFF);

	EXTERNAL_IRQ_0_init();

	EVENT_SYSTEM_0_init();

	CAMERA_OV7670_init();

	EDBG_COM_init();

	PCC_SCCB_init();

	delay_driver_init();

	PWM_0_init();
}
