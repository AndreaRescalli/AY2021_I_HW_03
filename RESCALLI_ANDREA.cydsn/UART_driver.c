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
//
//// Includes
//#include "UART_driver.h"
//#include <stdio.h>
//
//// Defines
//#define IDLE_STATE   0
//#define HEADER_STATE 1
//#define RED_STATE    2
//#define GREEN_STATE  3
//#define BLUE_STATE   4
//#define TAIL_STATE   5
//
//#define HEADER 0xA0
//#define TAIL   0xC0
//
//// Globals
//extern char recieved;
//extern uint8 dim;
//extern uint8 state;
//extern uint8 flag_rx;
//extern uint8 flag_five_sec;
//extern uint8 counter_timer;
//extern uint8 flag_rgb;
//extern RGB_struct rgb_values;
//uint8 dim = 0;
//uint8 rx = 0;
//uint8 i = 0;
//char bytes_acquired[20] = {'\0'};
//char acquired_data[20] = {'\0'};
//
//char header[20] = {'\0'};
//uint8 header_val = 0;
//
//char red[20] = {'\0'};
//uint8 red_val = 0;
//
//char green[20] = {'\0'};
//uint8 green_val = 0;
//
//char blue[20] = {'\0'};
//uint8 blue_val = 0;
//
//char tail[20] = {'\0'};
//uint8 tail_val = 0;
//
//
//
//
//// Function that acquires the packet recieved by the PSoC via UART protocol
//void acquire_data(uint8 *array) {
//    
//    if (flag_rx) {
//        
//        // If we have data in the RX BUFFER we acquire them
//        while(UART_GetRxBufferSize()) {
//            
//            array[i] = UART_GetChar();
//            //sprintf(acquired_data, "%i \r\n", array[i]);
//            //UART_PutString(acquired_data);
//            i++;
//            
//            // Check on the number of inputs. The packet must have a specifc length
//            if (i>5) {
//                UART_PutString("Error: too many inputs\r\n");
//                i = 0;
//                flag_rx = 0;
//                return;
//            }
//            
//        }
//        
//        // Get info on how many bytes we have recieved
//        sprintf(bytes_acquired, "Bytes acquired: %i\r\n", i);
//        UART_PutString(bytes_acquired);
//        
//        if (i<5) {
//            
//            // New data has to be acquired
//            switch(i) {
//                case 1:
//                    // Only header has been acquired
//                    UART_PutString("Enter RGB and tail\r\n");
//                    flag_rx = 0;
//                    break;
//                case 2:
//                    // Only header and RED have been acquired
//                    UART_PutString("Enter GB and tail\r\n");
//                    flag_rx = 0;
//                    break;
//                case 3:
//                    // BLUE and tail are missing
//                    UART_PutString("Enter B and tail\r\n");
//                    flag_rx = 0;
//                    break;
//                case 4: 
//                    // Only tail is missing
//                    UART_PutString("Enter tail\r\n");
//                    flag_rx = 0;
//                    break;
//                default:
//                    // Error
//                    UART_PutString("Error, please re-enter full package\r\n");
//                    i = 0;
//                    flag_rx = 0;
//                    break;
//            }
//            
//        }
//        else { // If we have acquired 5 bytes
//        
//            if (array[0] == HEADER) {
//                header_val = array[0];
//                sprintf(header, "HEADER: %i\r\n", header_val);
//                UART_PutString(header);
//            }
//            
//            if (array[1] == 0xFF) {
//                red_val = array[1];
//                sprintf(red, "RED:    %i\r\n", red_val);
//                UART_PutString(red);
//            }
//            
//            if (array[2] == 0xFF) {
//                green_val = array[2];
//                sprintf(green, "GREEN:  %i\r\n", green_val);
//                UART_PutString(green);
//            }
//             
//            if (array[3] == 0xFF) {
//                blue_val = array[3];
//                sprintf(blue, "BLUE:   %i\r\n", blue_val);
//                UART_PutString(blue);
//            }
//             
//            if (array[4] == TAIL) {
//                tail_val = array[4];
//                sprintf(tail, "TAIL:   %i\r\n", tail_val);
//                UART_PutString(tail);
//            }
//            
//            i = 0;
//            flag_rx = 0;
//            
//        }
//        
//    }
//    
//}
//
//
//// Function that represents the idle state (basically it waits for data and checks the header)
//void idle(uint8 *data) {
//    
//    // Reset the timer and clear all the data in the Rx buffer
//    reset_timer();
//    UART_ClearRxBuffer();
//                
//    UART_PutString("Enter RGB piloting commands (hex)\r\n");
//    
//    if (flag_rx) {
//        
//        // Save the first recieved byte, the header
//        data[state] = UART_ReadRxData();
//        flag_rx = 0;
//        
//        // Check wheather the header is correct
//        if (data[state] == HEADER) {
//            // Pass to the next state
//            state = HEADER_STATE;
//        }
//        else {
//            UART_PutString("Header byte not aknowledged\r\n");
//        }
//        
//    }    
//    
//} // end idle
//
//
///* 
// * Function that checks if we have other data.
// * If not, after 5s goes back to the IDLE_STATE;
// * If yes, goes on to RED_STATE
//*/
//void check_header(uint8 *data) {
//    
//    // Reset timer
//    reset_timer();
//    
//    while(!flag_five_sec && !flag_rx) {
//        // Wait for new data or 5 sec to run out
//    }
//    
//    // We exit the while if:
//    // 1) The package was not complete and we do not complete it within 5s
//    if (flag_five_sec) {
//        
//        UART_PutString("Timeout\r\n");
//        // Ready to recieve another package
//        flag_rx = 0;        // It should be already 0 since no bytes have been found, but better be sure
//        flag_five_sec = 0;  // Useless since it will be put to 0 by the reset_timer in the IDLE_STATE, but better be sure
//        state = IDLE_STATE;
//        
//    }
//    
//    // 2) The package had another byte, or a new one had beed recieved before timeout
//    if (flag_rx) {
//        
//        // Save the next byte in the Rx buffer (RED encoding)
//        data[state] = UART_ReadRxData();
//        
//        // Ready to recieve another byte
//        flag_rx = 0;
//        state = RED_STATE;
//    
//    }
//
//} // end check_header
//
//
//uint8 check_red(RGB_struct RGB, uint8 data) {
//
//    // Reset timer
//    reset_timer();
//    
//    // Save the recieved data into the struct for the RGB control
//    RGB.red_value = data;
//    
//    while(!flag_five_sec && !flag_rx) {
//        // Wait for new data or 5 sec to run out
//    }
//    
//    // We exit the while if:
//    // 1) 5 sec have passed
//    if (flag_five_sec) {
//        
//        UART_PutString("Timeout\r\n");
//        // Ready to recieve another byte
//        flag_rx = 0; // Useless since it should be already 0, but better be sure
//        flag_five_sec = 0; // Useless since it will be put to 0 by the reset_timer, but better be sure
//        state = IDLE_STATE;
//        
//        rx = 0;
//        
//    }
//    
//    // 2) A new data has been recieved
//    if (flag_rx) {
//        
//        // Save the recieved byte
//        rx = UART_GetChar();
//        
//        // Ready to recieve another byte
//        flag_rx = 0;
//        state = GREEN_STATE;
//    
//    }
//    
//    return rx;
//        
//} // end check_red
//
//
//uint8 check_green(RGB_struct RGB, uint8 data) {
//
//    // Reset timer
//    reset_timer();
//    
//    // Save the recieved data into the struct for the RGB control
//    RGB.green_value = data;
//    
//    while(!flag_five_sec && !flag_rx) {
//        // Wait for new data or 5 sec to run out
//    }
//    
//    // We exit the while if:
//    // 1) 5 sec have passed
//    if (flag_five_sec) {
//        
//        UART_PutString("Timeout\r\n");
//        // Ready to recieve another byte
//        flag_rx = 0; // Useless since it should be already 0, but better be sure
//        flag_five_sec = 0; // Useless since it will be put to 0 by the reset_timer, but better be sure
//        state = IDLE_STATE;
//        
//        rx = 0;
//        
//    }
//    
//    // 2) A new data has been recieved
//    if (flag_rx) {
//        
//        // Save the recieved byte
//        rx = UART_GetChar();
//        
//        // Ready to recieve another byte
//        flag_rx = 0;
//        state = BLUE_STATE;
//    
//    }
//    
//    return rx;
//    
//} // end check_green
//
//
//uint8 check_blue(RGB_struct RGB, uint8 data) {
//
//    // Reset timer
//    reset_timer();
//    
//    // Save the recieved data into the struct for the RGB control
//    RGB.blue_value = data;
//    
//    while(!flag_five_sec && !flag_rx) {
//        // Wait for new data or 5 sec to run out
//    }
//    
//    // We exit the while if:
//    // 1) 5 sec have passed
//    if (flag_five_sec) {
//        
//        UART_PutString("Timeout\r\n");
//        // Ready to recieve another byte
//        flag_rx = 0; // Useless since it should be already 0, but better be sure
//        flag_five_sec = 0; // Useless since it will be put to 0 by the reset_timer, but better be sure
//        state = IDLE_STATE;
//        
//        rx = 0;
//        
//    }
//    
//    // 2) A new data has been recieved
//    if (flag_rx) {
//        
//        // Save the recieved byte
//        rx = UART_GetChar();
//        
//        // Ready to recieve another byte
//        flag_rx = 0;
//        state = TAIL_STATE;
//    
//    }
//    
//    return rx;
//    
//} // end check_blue
//
//
///* 
// * Function that checks if the last byte recieved is correct.
// * If not, goes back to the IDLE_STATE;
// * If it is correct, allows the RGB PWM control and goes back to IDLE_STATE
//*/
//void check_tail(uint8 data) {
//    
//    // Reset timer
//    reset_timer();
//    
//    // Check if the data corresponds to the tail byte
//    if (data == TAIL) {
//        
//        // Get ready to recieve another byte
//        flag_rx = 0;
//        
//        // Tell the user the procedure was successful
//        UART_PutString("RGB succesfully piloted\r\n");
//        
//        // Enable RGB control
//        flag_rgb = 1;
//        
//    }
//    else {
//        
//        UART_PutString("Tail byte not aknowledged\r\n");
//        // Ready to recieve another byte
//        flag_rx = 0;
//        state = IDLE_STATE;
//        
//    }
//
//}
//
//
//// Reset of the timer
//void reset_timer(void) {
//    
//    // Reset the timer
//    Timer_Stop();
//    Timer_WriteCounter(249);
//    Timer_Enable();
//    counter_timer = 0;
//    flag_five_sec = 0;
//    
//}

/* [] END OF FILE */
