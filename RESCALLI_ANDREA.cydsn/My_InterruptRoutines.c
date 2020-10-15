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

#include "My_InterruptRoutines.h"
#include "UART.h"

extern uint8 flag_rx;
extern uint8 flag_five_sec;
extern uint8 counter_timer;

// Body of UART ISR based on the reception of a byte
CY_ISR(Custom_UART_RX_ISR) {

    // Check UART status
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
        flag_rx = 1;
    }
    
}


// Body of TIMER ISR based on tc
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