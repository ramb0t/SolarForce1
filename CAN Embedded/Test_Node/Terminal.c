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

	while(uart_available()){
		input[index++] = uart_getc(); // read a byte out

		if(index >= TERMINAL_MAX_INPUT_LENGTH){
			// Error!
			uart_puts("\n");
			uart_puts("Input Too Long!");
			return;
		}
	}

	// clear the input chars
	for(int i = index ; index < TERMINAL_MAX_INPUT_LENGTH+1; index++){
		input[i] = 0;
	}

	if(strcasecmp(input, TERMINAL_sCANCEL) == 0){ // Cancel
			*state = TERMINAL_RUN;
			uart_puts("\n");
			uart_puts("Cancelled\n");
			uart_puts("\n");
			Terminal_showMenu();
			return;
	}
	else if(strcasecmp(input, TERMINAL_sHELP) == 0){ // Help
		Terminal_showMenu();
		return;
	}
	else if(strcasecmp(input, TERMINAL_sLISTEN) == 0){ // Mode 1
		*state = TERMINAL_LISTEN;
		uart_puts("\n");
		uart_puts("Entering Listen Mode\n");
		uart_puts("Type 'c' to exit\n");
		uart_puts("\n");
		return;
	}
	else if(strcasecmp(input, TERMINAL_sLISTENRAW) == 0){ // Mode 2
		*state = TERMINAL_LISTENRAW;
		uart_puts("\n");
		uart_puts("Entering Listen Mode RAW\n");
		uart_puts("Type 'c' to exit\n");
		uart_puts("\n");
		return;
	}
	else if(strcasecmp(input, TERMINAL_sSEND1) == 0){ // Mode 2
			*state = TERMINAL_SEND1;
			uart_puts("\n");
			uart_puts("Sending MPPT Request \n");
			uart_puts("\n");
			return;
		}

	else{
		uart_puts("\n");
		uart_puts("Sorry I did not understand that, please try again\n");


#if defined(DEBUG)
		uart_puts("String In: ");
		uart_puts(input);
		uart_puts("\n");
		uart_puts("String Help: ");
		uart_puts(TERMINAL_sHELP);
		uart_puts("\n");
#endif


		return;
	}
	return;

}

/*************************************************************************
Function: Terminal_run()
Purpose:  Run the terminal
Input:    state pointer
Returns:  None
**************************************************************************/
void Terminal_run(uint8_t* state){

	switch (*state){
	case (TERMINAL_INIT):

			break;
	case (TERMINAL_RUN):

		break;
	case (TERMINAL_LISTEN):

		break;
	case (TERMINAL_LISTENRAW):

		break;
	case (TERMINAL_SEND1):

		break;
	default:
		uart_puts("Invalid State!\n");
		break;
	}

}

/*************************************************************************
Function: Terminal_showMenu()
Purpose:  Show the menu
Input:    None
Returns:  None
**************************************************************************/
static void Terminal_showMenu(void){
	uart_puts("\n");
	uart_puts("-------------------------------------\n");
	uart_puts("Main Menu:\n");
	uart_puts("1: Listen All CAN data Readable\n");
	uart_puts("2: Listen All CAN data Raw\n");
	uart_puts("3: Listen for Specified CAN ID \n");
	uart_puts("4: Send Single CAN Message\n");
	uart_puts("5: Loop Single CAN Message\n");
	uart_puts("-------------------------------------\n");
	uart_puts("\n");
	uart_puts("Type 'help' to show this menu again\n");

}
