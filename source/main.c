/*
 vim: et sw=4 ts=4:
 */
/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "display.h"
#include "screen_bits.h"
#include "screens.h"

static void wait()
{
    long int cycles = 10000000;
    while (cycles--)
    {
        __NOP();
    }
}

void (*fn[])() = {
                   display_circles1,
                   display_circles2,
                   display_ellipses1,
                   display_frames1,
                   display_frames2,
                   display_frames3,
                   display_main,
                   NULL
};



/*!
 * @brief Application entry point.
 */
int main(void)
{

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();


    display_init();
    
    display_images(0);
    wait();

    for(;;) { /* Infinite loop to avoid leaving the main function */
        __asm("NOP"); /* something to use as a breakpoint stop while looping */
    }
}
