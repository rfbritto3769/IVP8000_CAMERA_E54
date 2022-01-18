/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_ext_irq.h>

#include <hal_evsys.h>

#include <hal_camera_async.h>

#include <hal_usart_async.h>

#include <hal_i2c_m_sync.h>

#include <hal_delay.h>

#include <hal_pwm.h>
#include <hpl_tcc.h>

extern struct camera_async_descriptor CAMERA_OV7670;
extern uint32_t                       frame_buf[];
extern struct usart_async_descriptor  EDBG_COM;

extern struct i2c_m_sync_desc PCC_SCCB;

extern struct pwm_descriptor PWM_0;

void CAMERA_OV7670_PORT_init(void);
void CAMERA_OV7670_CLOCK_init(void);
void CAMERA_OV7670_init(void);

void EDBG_COM_PORT_init(void);
void EDBG_COM_CLOCK_init(void);
void EDBG_COM_init(void);

void PCC_SCCB_CLOCK_init(void);
void PCC_SCCB_init(void);
void PCC_SCCB_PORT_init(void);

void delay_driver_init(void);

void PWM_0_PORT_init(void);
void PWM_0_CLOCK_init(void);
void PWM_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
