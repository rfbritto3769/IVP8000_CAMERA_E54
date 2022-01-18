/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAME54 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13

#define PCC_VSYNC GPIO(GPIO_PORTA, 12)
#define PCC_HSYNC GPIO(GPIO_PORTA, 13)
#define PCC_PCLK GPIO(GPIO_PORTA, 14)
#define PCC_DATA0 GPIO(GPIO_PORTA, 16)
#define PCC_DATA1 GPIO(GPIO_PORTA, 17)
#define PCC_DATA2 GPIO(GPIO_PORTA, 18)
#define PCC_DATA3 GPIO(GPIO_PORTA, 19)
#define PCC_DATA4 GPIO(GPIO_PORTA, 20)
#define PCC_DATA5 GPIO(GPIO_PORTA, 21)
#define PCC_DATA6 GPIO(GPIO_PORTA, 22)
#define PCC_DATA7 GPIO(GPIO_PORTA, 23)
#define PB14 GPIO(GPIO_PORTB, 14)
#define PC11 GPIO(GPIO_PORTC, 11)
#define PC12 GPIO(GPIO_PORTC, 12)
#define PCC_PWDN GPIO(GPIO_PORTC, 22)
#define PCC_RESET GPIO(GPIO_PORTC, 23)
#define PC27 GPIO(GPIO_PORTC, 27)
#define PC28 GPIO(GPIO_PORTC, 28)
#define PCC_SCCB_SDA GPIO(GPIO_PORTD, 8)
#define PCC_SCCB_SCL GPIO(GPIO_PORTD, 9)

#endif // ATMEL_START_PINS_H_INCLUDED
