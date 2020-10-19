/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  TIMER_ISR.c
 * \brief Source file for the Assignment_3 that defines ISR of the timer
 *
 * Sets the colour of an (external) RGB LED according to a packet of data sent to the PSoC.
 * UART_PutString commands are commented so that the code can work with the GUI. If PSoC is piloted
 * with CoolTerm, they can be un-commented and they guide the user throughout the procedure (in this case
 * a byte-per-byte sending is required, since the PutString task would not allow to catch the packet properly in time)
 *
 * \author: Andrea Rescalli
 * \date:   20/10/2020
 *
 * ========================================
*/

// Includes
#include "TIMER_ISR.h"
#include "Timer.h"

// Globals
extern uint8 counter_timer;
extern uint8 flag_five_sec;

CY_ISR(Custom_TIMER_ISR) {
    
    // We have an ISR each 250ms but we want an alarm each 5s
    counter_timer++;
    
    // When 5 sec have passed
    if (counter_timer == 20) {
        flag_five_sec = 1;
        counter_timer = 0;
    }
    
    // Read timer status to bring interrupt line low
    Timer_ReadStatusRegister();

}

/* [] END OF FILE */
