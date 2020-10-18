/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  RGB_driver.h
 * \brief Driver file for the Assignment_3 that sets the PWM of the RGB LED channels
 *        according to the acquired data
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

#ifndef __RGB_DRIVER_H__
    #define __RGB_DRIVER_H__
    
    #include "cytypes.h"
    
    // Declaration of function that pilots the RGB LED based on recieved data
    void pilot_pwm(uint8 *buffer);
#endif

/* [] END OF FILE */
