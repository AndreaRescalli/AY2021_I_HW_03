/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// Includes
#include "Utilities.h"
#include "Timer.h"
#include "PWM_Red.h"
#include "PWM_Green.h"
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
    PWM_Red_Start();
    PWM_Green_Start();
    PWM_Blue_Start();

} // end PWM_Start

/* [] END OF FILE */
