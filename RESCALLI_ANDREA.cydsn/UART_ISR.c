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
#include "UART_ISR.h"
#include "UART.h"

// Globals
extern uint8 flag_rx;

CY_ISR(Custom_UART_RX_ISR) {

    // Check UART status
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
        flag_rx = 1;
    }
    
}

/* [] END OF FILE */
