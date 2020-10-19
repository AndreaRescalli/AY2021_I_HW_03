/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  UART_driver.c
 * \brief Driver file for the Assignment_3 that exploits UART to acquire a packet of data
 *
 * Sets the colour of an (external) RGB LED according to a packet of data sent to the PSoC.
 * UART_PutString commands are commented so that the code can work with the GUI. If PSoC is piloted
 * with CoolTerm, they can be un-commented and they guide the user throughout the procedure (in this case
 * a byte-per-byte sending is required, since the PutString task would not allow to catch the packet properly in time)
 *
 * \author: Andrea Rescalli
 * \date:   20/10/2020
 *
 * ========================================
*/

// Includes
#include "project.h"
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
extern uint8 flag_rx;
extern uint8 flag_packet;
extern uint8 flag_five_sec;
extern uint8 counter_timer;
extern uint8 state;
extern uint8 check;


//char recieved[25] = {'\0'};


// Definition of function that handles incoming bytes
void acquire_byte(uint8 *buffer) {

    if(flag_rx) {
        
        // Reset the timer
        reset_timer();
        
        // Update state
        state++;
        
        // Acquire data and communicate it
        check = UART_ReadRxData();
        flag_rx = 0;
        //sprintf(recieved, "Byte recieved: %i\r\n", check);
        //UART_PutString(recieved);
        
        // Special character for GUI can be typed at any time
        if(check == 'v') {
            // Reset the buffer
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 0;
            buffer[4] = 0;
            state = IDLE;
            
            // Display special message
            UART_PutString("RGB LED Program $$$\r\n");
        }
        
        switch(state) {
            
            case HEAD:
                if(check == HEADER_BYTE) {
                    // We accept the byte 
                    buffer[state-1] = check;
                    //UART_PutString("Please, send RED (hex)\r\n");
                }
                else {
                    //UART_PutString("Header byte not correct. Re-send byte\r\n");
                    state = IDLE;
                }
                break;
        
            case RED: 
                buffer[state-1] = check;
                //UART_PutString("Please, send GREEN (hex)\r\n");
                break;
        
            case GREEN:
                buffer[state-1] = check;
                //UART_PutString("Please, send BLUE (hex)\r\n");
                break;
            
            case BLUE:
                buffer[state-1] = check;
                //UART_PutString("Please, send tail byte\r\n");
                break;
           
            case TAIL:
                if(check == TAIL_BYTE) {
                    // We accept the byte
                    buffer[state-1] = check;
                    // We communicate we've acquired the full packet and we go back to IDLE
                    flag_packet = 1;
                    state = IDLE;
                }
                else {
                    //UART_PutString("Tail byte not correct. Re-send packet\r\n");
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


} // end acquire_byte

/* [] END OF FILE */
