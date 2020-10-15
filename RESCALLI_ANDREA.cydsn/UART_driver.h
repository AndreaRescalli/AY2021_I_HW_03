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

#ifndef __UART_DRIVER_H__
    #define __UART_DRIVER_H__
    
    // Includes
    #include "project.h"
    
    // Declaration of functions that will perform analysis and control on the input bytes
    void check_header(char byte);
    void check_red(char byte);
    void check_green(char byte);
    void check_blue(char byte);
    void check_tail(char byte);
    
    // Declaration of the function that resets the timer
    void reset_timer(void);

    
#endif

/* [] END OF FILE */
