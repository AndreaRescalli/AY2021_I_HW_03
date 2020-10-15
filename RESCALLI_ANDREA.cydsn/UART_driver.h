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
    
    // Struct to memorize the RGB values
    typedef struct {

        uint8 red_value;
        uint8 green_value;
        uint8 blue_value;

    } RGB_struct; 
    
    // Declaration of function that acquires a packet of data
    
    // Declaration of functions that will perform analysis and control on the input bytes
    void idle(uint8 *data);
    void check_header(uint8 *data);
    uint8 check_red(RGB_struct RGB, uint8 data);
    uint8 check_green(RGB_struct RGB, uint8 data);
    uint8 check_blue(RGB_struct RGB, uint8 data);
    void check_tail(uint8 data);
    
    // Declaration of the function that resets the timer
    void reset_timer(void);

    
#endif

/* [] END OF FILE */
