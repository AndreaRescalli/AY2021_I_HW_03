/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  UART_ISR.c
 * \brief Source file for the Assignment_3 that defines ISR of the UART
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
#include "UART_ISR.h"
#include "UART.h"

// Globals
extern uint8 flag_rx;

CY_ISR(Custom_UART_RX_ISR) {

    // Check UART status
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
        // If we have recieved a byte, communicate it
        flag_rx = 1;
    }
    
}

/* [] END OF FILE */
