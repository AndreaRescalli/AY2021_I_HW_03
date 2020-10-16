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
#include "RGB_driver.h"

/*
 * Function that initializes PWMs for each RGB channel.
 * Parameters are set in the schematic so as to have, as initial configuration of the RGB, a black colour (RGB OFF)
*/
void PWM_Start(void) {

    PWM_Red_Start();
    PWM_Green_Start();
    PWM_Blue_Start();

}
//
//void pwm_rgb(RGB_struct RGB) {
//    
//    /*
//     * Write the right compare value for each channel.
//     * REMEMBER: Channels are active if PWM is low, since the RGB is in common anode configuration --> PWM set as 'Less or Equal'
//     * For this reason, the compare setting has to be set as 255 - input (for example, if we want black we have to set (255-0,255-0,255-0); 
//     * in this way we put the PWM all HIGH and the RGB channel is always off).
//    */
//    PWM_Red_WriteCompare(255 - RGB.red_value);
//    PWM_Green_WriteCompare(255 - RGB.green_value);
//    PWM_Blue_WriteCompare(255 - RGB.blue_value);
//
//}

/* [] END OF FILE */
