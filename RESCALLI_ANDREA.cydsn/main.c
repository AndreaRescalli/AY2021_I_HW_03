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
uint8 flag_rx = 0;
uint8 flag_packet = 0;
uint8 flag_five_sec = 0;
uint8 counter_timer = 0;;

uint8 check = 0;
uint8 buffer[PACKET_SIZE] = {0};
uint8 state = IDLE;

char recieved[25] = {'\0'};
char red_val[25] = {'\0'};
char green_val[25] = {'\0'};
char blue_val[25] = {'\0'};



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // Enable ISRs
    isr_UART_StartEx(Custom_UART_RX_ISR);
    isr_TIMER_StartEx(Custom_TIMER_ISR);
    // Start UART
    UART_Start();
    // Start TIMER
    Timer_Start();
    // Start PWM
    PWM_Start();    
    
    // Init command
    UART_PutString("Please, send header byte\r\n");


    for(;;)
    {
        
        if(flag_rx) {
            
            // Reset the timer
            reset_timer();
            
            // Update state
            state++;
            
            // Acquire data and communicate it
            check = UART_ReadRxData();
            flag_rx = 0;
            sprintf(recieved, "Byte recieved: %i\r\n", check);
            UART_PutString(recieved);
            
            switch(state) {
                
                case HEAD:
                    if(check == HEADER_BYTE) {
                        // We accept the byte 
                        buffer[state-1] = check;
                        UART_PutString("Please, send RED (hex)\r\n");
                    }
                    else {
                        UART_PutString("Header byte not correct. Re-send byte\r\n");
                        state = IDLE;
                    }
                    break;
            
                case RED: 
                    buffer[state-1] = check;
                    UART_PutString("Please, send GREEN (hex)\r\n");
                    break;
            
                case GREEN:
                    buffer[state-1] = check;
                    UART_PutString("Please, send BLUE (hex)\r\n");
                    break;
                
                case BLUE:
                    buffer[state-1] = check;
                    UART_PutString("Please, send tail byte\r\n");
                    break;
               
                case TAIL:
                    if(check == TAIL_BYTE) {
                        buffer[state-1] = check;
                        flag_packet = 1;
                        state = IDLE;
                    }
                    else {
                        UART_PutString("Tail byte not correct. Re-send packet\r\n");
                        // Reset the buffer
                        buffer[0] = 0;
                        buffer[1] = 0;
                        buffer[2] = 0;
                        buffer[3] = 0;
                        buffer[4] = 0;
                        state = IDLE;
                    }
                    break;
                    
                default:
                    // We're in IDLE
                    break;
                    
            } // end switch-case
           
        } // end if(flag_rx)
        
        // When we're not in IDLE or TAIL, we have a time window within which we can accept bytes
        if(state == HEAD || state == RED || state == GREEN || state == BLUE) {
            if(flag_five_sec) {
                // 5s timeout has occurred. We have to discard data and get back to IDLE state
                UART_PutString("Timeout. Re-send packet\r\n");
                buffer[0] = 0;
                buffer[1] = 0;
                buffer[2] = 0;
                buffer[3] = 0;
                buffer[4] = 0;
                flag_five_sec = 0;
                state = IDLE;
            }
        }
        
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
               
    } // end for
    
} // end main

/* [] END OF FILE */
