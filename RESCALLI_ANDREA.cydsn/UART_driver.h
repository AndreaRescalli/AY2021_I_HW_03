/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  UART_driver.h
 * \brief Driver file for the Assignment_3 that exploits UART to acquire a packet of data
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

#ifndef __UART_DRIVER_H__
    #define __UART_DRIVER_H__
    
    #include "cytypes.h"
    
    // Declaration of function that handles incoming bytes
    void acquire_byte(uint8 *buffer);
#endif

/* [] END OF FILE */
