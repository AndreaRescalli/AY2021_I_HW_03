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

// Globals
uint8 flag_rx = 0;                  // flag for the UART rx
uint8 counter_timer = 0;            // counts the overflows of the timer
uint8 flag_five_sec = 0;            // flag to inform 5 seconds have passed
uint8 recieved = 0;                 // recieved byte
uint8 state = IDLE_STATE;           // variable that keeps track of the state of the decoding process
uint8 flag_rgb = 0;                 // flag to inform the reception was successful
RGB_struct rgb_values = {0, 0, 0};  // struct that will preserve the recieved values for the RGB channels
uint8 packet[PACKET_SIZE] = {0};    // array in which we store the input packet


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
        
        acquire_data(packet);
        
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
