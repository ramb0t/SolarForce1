/*
 * Terminal.c
 *
 *  Created on: 01 Apr 2015
 *      Author: RobThePyro
 */

#include "Terminal.h"



/*************************************************************************
Function: Terminal_init()
Purpose:  Setup the terminal interface
Input:    None
Returns:  None
**************************************************************************/
void Terminal_init(void){
	Terminal_showMenu();
}

/*************************************************************************
Function: Terminal_read()
Purpose:  Read the uart interface and process
Input:    state pointer
Returns:  None
**************************************************************************/
void Terminal_read(uint8_t* state){

	// input char array
	char input[TERMINAL_MAX_INPUT_LENGTH+1];
	// index pointer
	uint8_t index = 0;

	while(uart1_available()){
		input[index++] = uart1_getc(); // read a byte out

		if(index >= TERMINAL_MAX_INPUT_LENGTH){
			// Error!
			uart_puts("Input Too Long!");
			return;
		}
	}

	if(strcmp(input, TERMINAL_HELP)){
		Terminal_showMenu();
		return;
	}else{
		uart1_puts("Sorry I did not understand that, please try again\n");
		return;
	}

}

/*************************************************************************
Function: Terminal_run()
Purpose:  Run the terminal
Input:    state pointer
Returns:  None
**************************************************************************/
void Terminal_run(uint8_t* state){

}

/*************************************************************************
Function: Terminal_showMenu()
Purpose:  Show the menu
Input:    None
Returns:  None
**************************************************************************/
static void Terminal_showMenu(void){
	uart1_puts("Main Menu:\n");
	uart1_puts("1: Listen All CAN data\n");
	uart1_puts("2: Listen for Specified CAN ID \n");
	uart1_puts("3: Send Single CAN Message\n");
	uart1_puts("4: Loop Single CAN Message\n");
	uart1_puts("-------------------------------------/n");
	uart1_puts("Type 'help' to show this menu again\n\n");

}
