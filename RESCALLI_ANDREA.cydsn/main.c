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
#include "stdio.h"

// Defines
#define IDLE_STATE   0
#define HEADER_STATE 1
#define RED_STATE    2
#define GREEN_STATE  3
#define BLUE_STATE   4
#define TAIL_STATE   5

// Globals
uint8 flag_rx = 0;          // flag for the UART rx
uint8 counter_timer = 0;    // counts the overflows of the timer
uint8 flag_five_sec = 0;    // flag to inform 5 seconds have passed
char recieved = {'\0'};     // recieved byte
uint8 state = IDLE_STATE;   // variable that keeps track of the state of the decoding process
uint8 flag_rgb = 0;         // flag to inform the reception was successful

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // Enable ISRs
    isr_UART_StartEx(Custom_UART_RX_ISR);
    isr_TIMER_StartEx(Custom_TIMER_ISR);
    // Start UART
    UART_Start();
    // Start Timer
    Timer_Start();


    for(;;)
    {
        
        switch(state) {
            
            case IDLE_STATE:
                reset_timer();
                
                UART_PutString("Enter header encoding (hex)\r\n");
                while(!flag_rx) {
                    // Wait for data
                }
                // Save the recieved byte
                recieved = UART_ReadRxData();
                
                // Pass to the next state
                state = HEADER_STATE;
            break;
                
            case HEADER_STATE:
                check_header(recieved);
            break;
                
            case RED_STATE:
                check_red(recieved);
            break;
                
            case GREEN_STATE:
                check_green(recieved);
            break;
                
            case BLUE_STATE:
                check_blue(recieved);
            break;
                
            case TAIL_STATE:
                check_tail(recieved);
            break;
                
        } // end switch/case
        
        if (flag_rgb) {
        
            // Pilot the PWM based on the values recieved
            /*
             * PWM settato come 'less or equal'.
             * questo perchè un segnale PWM basso implica LED ON, mentre alto LED OFF
             * quindi siccome parte da 255, se ad esempio voglio nero (0,0,0) devo dargli (255-0,255-0,255-0)
             * Se voglio grigio, che è 128,128,128, il DC è del 50% --> compare settato a 255-128 = 127
             * COMPARE = 255 - ciò che ricevo in input
             *
            */ 
        
        } // end rgb if
        
    } // end for
} // end main

/* [] END OF FILE */
