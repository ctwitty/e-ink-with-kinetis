/*
 vim: ts=4 sw=4 et:
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

gpio_pin_config_t pin_as_output_low = { kGPIO_DigitalOutput, 0 };
gpio_pin_config_t pin_as_output_high = { kGPIO_DigitalOutput, 1 };
gpio_pin_config_t pin_as_input = { kGPIO_DigitalInput, 0 };

/* Function Name : BOARD_InitPins */
void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortA);
    CLOCK_EnableClock(kCLOCK_PortE);
    CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);

    /* e-ink reset output, active low */
    PORT_SetPinMux(PORTE, 0u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 0u, &pin_as_output_high);
    /* D/~C */
    PORT_SetPinMux(PORTE, 1u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 1u, &pin_as_output_high);
    /* BUSY */
    PORT_SetPinMux(PORTE, 18u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 18u, &pin_as_input);

/* The example code provided by the vendor has a software spi implementation.
   Let's try that first.  Down the road, we'd probably want to switch to
   the hardware assisted API.  I'm choosing the same pins to make that easy.
 */
#define USE_BITBANG_SPI 1
#if USE_BITBANG_SPI
    /* e-ink spi1_ss */
    PORT_SetPinMux(PORTE, 16u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 16u, &pin_as_output_high);
    /* e-ink spi1_clk */
    PORT_SetPinMux(PORTE, 17u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 17u, &pin_as_output_high);
    /* e-ink spi1_mosi */
    PORT_SetPinMux(PORTE, 19u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOE, 19u, &pin_as_output_high);
#else
    #error Hardware assisted SPI not implemented yet
    /* e-ink spi1_ss */
    PORT_SetPinMux(PORTE, 16u, kPORT_MuxAlt2);
    /* e-ink spi1_clk */
    PORT_SetPinMux(PORTE, 17u, kPORT_MuxAlt2);
    /* e-ink spi1_mosi, Alt 5 (not Alt 2) */
    PORT_SetPinMux(PORTE, 19u, kPORT_MuxAlt5);
#endif

    /* Pin header */
    PORT_SetPinMux(PORTD, 7u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOD, 7u, &pin_as_output_high);
    PORT_SetPinMux(PORTD, 6u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOD, 6u, &pin_as_output_low);
    PORT_SetPinMux(PORTD, 5u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOD, 5u, &pin_as_output_high);
    PORT_SetPinMux(PORTD, 4u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOD, 4u, &pin_as_output_low);
    PORT_SetPinMux(PORTC, 7u, kPORT_MuxAsGpio);
    GPIO_PinInit(GPIOC, 7u, &pin_as_output_high);
}
