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
#include "My_InterruptRoutines.h"
#include "UART_driver.h"
//#include "RGB_driver.h"
#include <stdio.h>

// Defines
#define IDLE_STATE   0
#define HEADER_STATE 1
#define RED_STATE    2
#define GREEN_STATE  3
#define BLUE_STATE   4
#define TAIL_STATE   5

#define PACKET_SIZE  5



// Added
#define HEADER 0xA0
#define TAIL   0xC0




// Globals
uint8 flag_rx = 0;                  // flag for the UART rx
uint8 counter_timer = 0;            // counts the overflows of the timer
uint8 flag_five_sec = 0;            // flag to inform 5 seconds have passed
uint8 recieved = 0;                 // recieved byte
uint8 state = IDLE_STATE;           // variable that keeps track of the state of the decoding process
uint8 flag_rgb = 0;                 // flag to inform the reception was successful
RGB_struct rgb_values = {0, 0, 0};  // struct that will preserve the recieved values for the RGB channels
uint8 packet[PACKET_SIZE] = {0};    // array in which we store the input packet



// Added
char header[20] = {'\0'};
uint8 header_val = 0;

char red[20] = {'\0'};
uint8 red_val = 0;

char green[20] = {'\0'};
uint8 green_val = 0;

char blue[20] = {'\0'};
uint8 blue_val = 0;

char tail[20] = {'\0'};
uint8 tail_val = 0;

uint8 dim = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // Enable ISRs
    isr_UART_StartEx(Custom_UART_RX_ISR);
    //isr_TIMER_StartEx(Custom_TIMER_ISR);
    // Start UART
    UART_Start();
    UART_EnableRxInt();
    // Start Timer
    //Timer_Start();
    // Start PWM
    //PWM_Start();
    
    
    UART_PutString("Enter RGB piloting commands (hex)\r\n");


    for(;;)
    {
        
        // commented now acquire_data(packet);
        // Added
        int i = 0;
        if (flag_rx) {
            for (i=0; i<PACKET_SIZE;i++) {
                packet[i] = (uint8) (UART_GetByte() & 0x00FF);
            }
            UART_ClearRxBuffer();
            
            if (packet[0] == HEADER) {
                header_val = packet[0];
                sprintf(header, "HEADER: %i\r\n", header_val);
                UART_PutString(header);
            }
            
            //if (packet[1] == 0xFF) {
                red_val = packet[1];
                sprintf(red, "RED:    %i\r\n", red_val);
                UART_PutString(red);
            //}
            
            //if (packet[2] == 0xFF) {
                green_val = packet[2];
                sprintf(green, "GREEN:  %i\r\n", green_val);
                UART_PutString(green);
            //}
             
            //if (packet[3] == 0xFF) {
                blue_val = packet[3];
                sprintf(blue, "BLUE:   %i\r\n", blue_val);
                UART_PutString(blue);
            //}
             
            if (packet[4] == TAIL) {
                tail_val = packet[4];
                sprintf(tail, "TAIL:   %i\r\n", tail_val);
                UART_PutString(tail);
            }
            
            flag_rx = 0;
        }
        
//        if (state == IDLE_STATE) {
//            idle(packet);
//        }
//            
//        else if (state == HEADER_STATE) {
//            check_header(packet);
//        }
//            
//        else if (state == RED_STATE) {
//            packet[state] = check_red(rgb_values, recieved);
//        }
//            
//        else if (state == GREEN_STATE) {
//            packet[state] = check_green(rgb_values, recieved);
//        }
//            
//        else if (state == BLUE_STATE) {
//            packet[state] = check_blue(rgb_values, recieved);
//        }
//            
//        else if (state == TAIL_STATE) {
//            check_tail(packet[state-1]);
//        }    
//                
//        
//        if (flag_rgb) {
//        
//            // Pilot the PWM based on the values recieved
//            pwm_rgb(rgb_values);
//            flag_rgb = 0;
//        
//        } // end rgb if
//        
//        
    } // end for
    
} // end main

/* [] END OF FILE */
