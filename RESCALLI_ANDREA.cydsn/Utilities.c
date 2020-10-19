/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  Utilities.c
 * \brief Source file for the Assignment_3 that defines some utility functions (reset of the timer and start of PWM)
 *
 * Sets the colour of an (external) RGB LED according to a packet of data sent to the PSoC.
 * UART_PutString commands are commented so that the code can work with the GUI. If PSoC is piloted
 * with CoolTerm, they can be un-commented and they guide the user throughout the procedure.
 *
 * \author: Andrea Rescalli
 * \date:   20/10/2020
 *
 * ========================================
*/

// Includes
#include "Utilities.h"
#include "Timer.h"
#include "PWM_Red_and_Green.h"
#include "PWM_Blue.h"

// Globals
extern uint8 flag_five_sec;
extern uint8 counter_timer;

// Definition of function that resets the timer
void reset_timer(void) {
    
    // Reset the timer
    Timer_Stop();
    Timer_WriteCounter(249);
    Timer_Enable();
    counter_timer = 0;
    flag_five_sec = 0; 
    
} // end reset_timer


// Definition of function to start PWM
void PWM_Start(void) {

    // Start each RGB channel's PWM
    PWM_Red_and_Green_Start();
    PWM_Blue_Start();

} // end PWM_Start

/* [] END OF FILE */
