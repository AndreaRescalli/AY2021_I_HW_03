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

#ifndef __RGB_DRIVER_H__
    
    #define __RGB_DRIVER_H__
    
    // Includes
    #include "project.h"
    #include "UART_driver.h"
    
    // Declaration of function that will drive the RGB
    void pwm_rgb(RGB_struct RGB);
    void PWM_Start(void);
    
#endif


/* [] END OF FILE */
