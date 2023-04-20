/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */

// Joann Carter

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>


/* Driver Header files */
#include <ti/drivers/GPIO.h>


/* Driver configuration */
#include "ti_drivers_config.h"
// added for 32 bit timer driver
#include <ti/drivers/Timer.h>

bool isButtonPressed; // boolenan for button press
uint32_t   dotTime = 150000; // 150 milliseconds to represent a dot
uint32_t   dashTime = 400000; // 400 millisecond to represent a dash
uint32_t   delayTime_char = 300000; // 300 millisecond  for delay between characters in word
uint32_t   delayTime_word = 1500000; // 1500 milliseconds for delay between words

volatile unsigned char TimerFlag = 0; // callback raises, main lowers
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    TimerFlag = 1;
}
void initTimer(void)
{
    Timer_Handle timer0;
    Timer_Params params;
    Timer_init();
    Timer_Params_init(&params);
    params.period = 500000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;





     timer0 = Timer_open(CONFIG_TIMER_0, &params);
     if (timer0 == NULL) {
     /* Failed to initialized timer */
     while (1) {}
     }
     if (Timer_start(timer0) == Timer_STATUS_ERROR) {
     /* Failed to start timer */
     while (1) {}
     }
}
/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn0(uint_least8_t index)
{
//    /* Toggle an LED */
//    GPIO_toggle(CONFIG_GPIO_LED_0);
    if(isButtonPressed){
        isButtonPressed = false; // set boolean for reference in SM
    }else{
        isButtonPressed = true;

    }
   // printf("button pressed button 0 : %d\n", isButtonPressed );

}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn1(uint_least8_t index)

{
     if(isButtonPressed){
         isButtonPressed = false; // set boolean for reference in SM
     }else{
         isButtonPressed = true;

     }
    // printf("button pressed button 1 : %d\n", isButtonPressed );

}


// transitions: button pushed on , button pushed off
// STATEs for LIGHTing LEDs
enum LIGHT_STATES { LIGHT_INIT, LIGHT_SOS, LIGHT_OK,  LIGHT_PAUSE } LIGHT_STATE;


// LED 0: red- symbolizes quick flash / dot
// LED 1: green- symbolizes long flash / dash

void flash_S(){
    // flashes red LED as 'S' in morse code ( 3 quick flashes-dots)


        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON); // turn on Light
        usleep(dotTime);                                      // wait for short delay
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF); // shut light off

        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON); // turn on Light
        usleep(dotTime);                                      // wait for short delay
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF); // shut light off

        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON); // turn on Light
        usleep(dotTime);                                      // wait for short delay
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF); // shut light off




}
void flash_O(){
    // flashes green LED as 'O' in morse code ( 3 long flashes-dashes)

        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON); // turn light on
        usleep(dashTime);                   // wait for long delay
        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF); // turn light off

        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON); // turn light on
        usleep(dashTime);                   // wait for long delay
        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF); // turn light off

        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON); // turn light on
        usleep(dashTime);                   // wait for long delay
        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF); // turn light off

        usleep(delayTime_char);                   // wait in between letters

}
void flash_K(){
    // flashes LEDs as 'K' in morse code ( dash(green LED), dot(red LED), dash(green LED))

        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON); // turn light on
        usleep(dashTime);                   // wait for long delay
        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF); // turn light off
        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON); // turn on Light
        usleep(dotTime);                                      // wait for short delay
        GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF); // shut light off
        usleep(delayTime_char);                   // wait in between letters

        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON); // turn light on
        usleep(dashTime);                   // wait for long delay
        GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF); // turn light off


    //    printf("flashed k\n" );

}

//// STATE Machine for Tick of LIGHTING LED MESSAGE
void TickFunc_Light(){
    switch(LIGHT_STATE){ // transitions
        case LIGHT_INIT:     // initial transition
            LIGHT_STATE = LIGHT_SOS;
            break;
        case LIGHT_SOS:
            break;
        case LIGHT_OK:
            break;
        case LIGHT_PAUSE:
            usleep(delayTime_word);                // wait in between letters
            if(isButtonPressed){  // change state based on button press
                LIGHT_STATE = LIGHT_OK;
            }else{
                LIGHT_STATE = LIGHT_SOS;
            }
            break;
        default:
            LIGHT_STATE = LIGHT_INIT;
            break;

    }



    switch(LIGHT_STATE){  //STATE Actions
        case LIGHT_INIT:
            break;
        case LIGHT_SOS:                     // send SOS message with LEDs
            flash_S();
            usleep(delayTime_char);         // wait in between letters
            flash_O();
            usleep(delayTime_char);         // wait in between letters
            flash_S();
             LIGHT_STATE = LIGHT_PAUSE;     // change state to pause and determine if button has been pressed
            break;
        case LIGHT_OK:                      // Send OK message with LEDs
            flash_O();
            usleep(delayTime_char);         // wait in between letters
            flash_K();
             LIGHT_STATE = LIGHT_PAUSE;     // change state to pause and determine if button has been pressed
            break;
        case LIGHT_PAUSE:

            break;
        default:
           LIGHT_STATE = LIGHT_INIT;
        }

}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{


    isButtonPressed = false; // init button to unpressed and message to SOS
    /* Call driver init functions */
    GPIO_init();
    initTimer();
    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

//    /* Turn on user LED */
//    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }
    LIGHT_STATE = LIGHT_INIT; // Indicates initial call
    while(1){
        TickFunc_Light(); // STATE MACHINE FOR MESSAGE OUTPUT WITH LEDS
        while(!TimerFlag){} // wait for period
        TimerFlag = 0;
    }
//return(NULL);

}
