/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  Utilities.h
 * \brief Header file for the Assignment_3 that declares some utility functions (reset of the timer and start of PWM)
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

#ifndef __UTILITIES_H__
    #define __UTILITIES_H__
    
    #include "cytypes.h"
    
    // Declaration of function that resets the timer
    void reset_timer(void);
    
    // Declaration of function to start PWM
    void PWM_Start(void);
#endif

/* [] END OF FILE */
