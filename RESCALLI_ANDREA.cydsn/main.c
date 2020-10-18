/* ========================================
 *
 * Copyright LTEBS srl, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF LTEBS srl.
 *
 * \file  main.c
 * \brief Main source file for the Assignment_3
 *
 * Sets the colour of an (external) RGB LED according to a packet of data sent to the PSoC.
 * UART_PutString commands are commented so that the code can work with the GUI. If PSoC is piloted
 * with CoolTerm, they can be un-commented and they guide the user throughout the procedure.
 *
 * \author: Andrea Rescalli
 * \date:   20/10/2020 
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
uint8 flag_rx = 0;
uint8 flag_packet = 0;
uint8 flag_five_sec = 0;
uint8 counter_timer = 0;

uint8 check = 0;
uint8 buffer[PACKET_SIZE] = {0};
uint8 state = IDLE;



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
    //UART_PutString("Please, send header byte\r\n");


    for(;;)
    {
        // Acquire and process incoming, single, bytes
        acquire_byte(buffer);
        
        // Act on the RGB LED based on recieved packet
        pilot_pwm(buffer);
               
    } // end for
    
} // end main

/* [] END OF FILE */
