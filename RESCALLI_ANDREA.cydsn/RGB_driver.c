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
#include "project.h"
#include "RGB_driver.h"
#include "UART_driver.h"
#include "UART_ISR.h"
#include "TIMER_ISR.h"
#include "Utilities.h"
#include <stdio.h>


// Defines
#define PACKET_SIZE 5

#define IDLE  0
#define HEAD  1
#define RED   2
#define GREEN 3
#define BLUE  4
#define TAIL  5

#define HEADER_BYTE 0xA0
#define TAIL_BYTE   0xC0


// Globals
extern uint8 flag_packet;
extern uint8 state;

char red_val[25] = {'\0'};
char green_val[25] = {'\0'};
char blue_val[25] = {'\0'};



// Definition of function that pilots the RGB LED based on recieved data
void pilot_pwm(uint8 *buffer) {
    
        if(flag_packet) {

        /*
         * Write the right compare value for each channel.
         * REMEMBER: Channels are active if PWM is low, since the RGB is in common anode configuration --> PWM set as 'Less or Equal'
         * For this reason, the compare setting has to be set as 255 - input (for example, if we want black we have to set (255-0,255-0,255-0); 
         * in this way we put the PWM all HIGH and the RGB channel is always off).
        */
        
        UART_PutString("\r\n");
        UART_PutString("---------------------------\r\n");
        UART_PutString("\r\n");
        UART_PutString("RGB updated:\r\n");
        sprintf(red_val, "RED:    %i\r\n", buffer[1]);
        UART_PutString(red_val);
        
        // Pilot RED PWM
        PWM_Red_WriteCompare(255 - buffer[1]);

        sprintf(green_val, "GREEN:  %i\r\n", buffer[2]);
        UART_PutString(green_val);
        
        // Pilot GREEN PWM
        PWM_Green_WriteCompare(255 - buffer[2]);

        sprintf(blue_val, "BLUE:   %i\r\n", buffer[3]);
        UART_PutString(blue_val);
        UART_PutString("\r\n");
        UART_PutString("---------------------------\r\n");
        UART_PutString("\r\n");
        
        // Pilot BLUE PWM
        PWM_Blue_WriteCompare(255 - buffer[3]);
        
        flag_packet = 0;
        // Reset the buffer and get ready for new acquisition
        buffer[0] = 0;
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
        buffer[4] = 0;
        state = IDLE;
        UART_PutString("Please, send header byte\r\n");
        
    }

}

/* [] END OF FILE */
