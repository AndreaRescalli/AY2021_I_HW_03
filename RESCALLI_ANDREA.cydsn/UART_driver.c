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
#include "UART_driver.h"

// Defines
#define IDLE_STATE   0
#define HEADER_STATE 1
#define RED_STATE    2
#define GREEN_STATE  3
#define BLUE_STATE   4
#define TAIL_STATE   5

#define HEADER 0xA0
#define TAIL   0xC0

// Globals
extern char recieved;
extern uint8 state;
extern uint8 flag_rx;
extern uint8 flag_five_sec;
extern uint8 counter_timer;
extern uint8 flag_rgb;

/* 
 * Function that checks if the first byte recieved is correct.
 * If not, goes back to the IDLE_STATE;
 * If it is correct, waits 5s for a new data; if in 5s no data are acquired, goes back to IDLE_STATE;
 *                                            if recieves a new data, goes on to RED_STATE
*/
void check_header(char recieved) {
    
    // Reset timer
    reset_timer();
    
    // Check if the data corresponds to the header byte
    if (recieved == HEADER) {
        
        // Get ready to recieve another byte
        flag_rx = 0;
        
        // Tell the user he can enter the next byte (RED encoding)
        UART_PutString("Enter RED encoding (hex)\r\n");
        
        while(!flag_five_sec && !flag_rx) {
            // Wait for new data or 5 sec to run out
        }
        
        // We exit the while if:
        // 1) 5 sec have passed
        if (flag_five_sec) {
            
            UART_PutString("Timeout\r\n");
            // Ready to recieve another byte
            flag_rx = 0; // Useless since it should be already 0, but better be sure
            flag_five_sec = 0; // Useless since it will be put to 0 by the reset_timer, but better be sure
            state = IDLE_STATE;
            
        }
        
        // 2) A new data has been recieved
        if (flag_rx) {
            
            // Save the recieved byte
            recieved = UART_ReadRxData();
            
            // Ready to recieve another byte
            flag_rx = 0;
            state = RED_STATE;
        
        }
        
    }
    else {
        
        UART_PutString("Header byte not aknowledged\r\n");
        // Ready to recieve another byte
        flag_rx = 0;
        state = IDLE_STATE;
        
    }

}

void check_red(char recieved) {

}

void check_green(char recieved) {

}

void check_blue(char recieved) {

}

/* 
 * Function that checks if the last byte recieved is correct.
 * If not, goes back to the IDLE_STATE;
 * If it is correct, allows the RGB PWM control and goes back to IDLE_STATE
*/
void check_tail(char recieved) {
    
    // Reset timer
    reset_timer();
    
    // Check if the data corresponds to the tail byte
    if (recieved == TAIL) {
        
        // Get ready to recieve another byte
        flag_rx = 0;
        
        // Tell the user the procedure was successful
        UART_PutString("RGB succesfully piloted\r\n");
        
        // Enable RGB control
        flag_rgb = 1;
        
    }
    else {
        
        UART_PutString("Tail byte not aknowledged\r\n");
        // Ready to recieve another byte
        flag_rx = 0;
        state = IDLE_STATE;
        
    }

}


// Reset of the timer
void reset_timer(void) {
    
    // Reset the timer
    Timer_Stop();
    Timer_WriteCounter(249);
    Timer_Enable();
    counter_timer = 0;
    flag_five_sec = 0;
    
}

/* [] END OF FILE */
