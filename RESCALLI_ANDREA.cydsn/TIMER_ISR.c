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
#include "TIMER_ISR.h"

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

}

/* [] END OF FILE */
