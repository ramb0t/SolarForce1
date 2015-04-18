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
void Terminal_read(volatile uint8_t* state){

	// input char array
	char input[TERMINAL_MAX_INPUT_LENGTH+1];  // defines the maximum string length that we are willing at accept
	// index pointer
	uint8_t index = 0;


	while(uart_available()){
		input[index] = uart_getc(); // read a byte out
		index++;
		_delay_ms(2); // wait incase of another byte


		if(index >= TERMINAL_MAX_INPUT_LENGTH){
			// Error!
			uart_puts("\n");
			uart_puts("Input Too Long!");
			*state = TERMINAL_RUN;
			return;
		}
	}

	// clear the excess input chars (init random ram)
	// could we not get away with setting next char to endline operator?
	for(int i = index ; index <= TERMINAL_MAX_INPUT_LENGTH; index++){
		input[i] = 0;
	}

	// do they want help ??
	if(strcasecmp(input, TERMINAL_sHELP) == 0){ // Help
		Terminal_showMenu();
		return;
	}

	// Lets see if we can find a command?
	uint8_t command = 0;
	if(input[0] >=48 || input[0] <= 57){ // in the range of 0-9 .. decode
		command = input[0] - 48;


		// now do state machine logic
		switch(*state){
		case TERMINAL_RUN :
			// Main Menu
			switch(command){
			case TERMINAL_cLISTENSUB:
				// Go to listen submenu
				*state = TERMINAL_LISTENSUB;
				uart_puts("\n");
				uart_puts("Entering Listen Submenu\n");
				Terminal_showListenMenu();
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cSENDSUB:
				// Go to send submenu
				*state = TERMINAL_SENDSUB;
				uart_puts("\n");
				uart_puts("Entering Send Submenu\n");
				Terminal_showSendMenu();
				uart_puts("\n");
				return;
				break;


			default:
				// Unknown Command
				uart_puts("\n");
				uart_puts("Unknown command!\n");
				Terminal_showMenu();
				uart_puts("\n");
				return;
				break;
			} // Main Command Switch
			break;

		case TERMINAL_LISTENSUB :
			// Listen Submenu
			switch(command){
			case TERMINAL_cLISTEN:
				// Go to Normal Listen Mode
				*state = TERMINAL_LISTEN;
				uart_puts("\n");
				uart_puts("Entering Listen Mode\n");
				uart_puts("Type 'c' to exit\n");
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cLISTENRAW:
				// Go to RAW Listen Mode
				*state = TERMINAL_LISTENRAW;
				uart_puts("\n");
				uart_puts("Entering Listen Mode RAW\n");
				uart_puts("Type 'c' to exit\n");
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cBACK:
				// Go Back To Main Menu
				*state = TERMINAL_RUN;
				uart_puts("\n");
				uart_puts("Back to Main Menu..\n");
				uart_puts("\n");
				Terminal_showMenu();
				return;
				break;

			default:
				// Unknown Command
				uart_puts("\n");
				uart_puts("Unknown command!\n");
				Terminal_showListenMenu();
				uart_puts("\n");
				return;
				break;
			} // Listen Command Switch
			break; // Listen Submenu


			case TERMINAL_SENDSUB :
			// Send Submenu
			switch(command){
			case TERMINAL_cSENDRANDOM:
				// Send Random Data
				*state = TERMINAL_SENDRANDOM;
				uart_puts("\n");
				uart_puts("Sending Random CAN Messages \n");
				uart_puts("Type 'c' to exit\n");
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cSENDBMS:
				// Send BMS Data
				*state = TERMINAL_SENDBMS;
				uart_puts("\n");
				uart_puts("Sending BMS CAN Messages \n");
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cLOOPBMS:
				// loop BMS Data
				*state = TERMINAL_LOOPBMS;
				uart_puts("\n");
				uart_puts("Looping BMS CAN Messages \n");
				uart_puts("Type 'c' to exit\n");
				uart_puts("\n");
				return;
				break;

			case TERMINAL_cLOOPSPEED:
				// loop Speed Data
				*state = TERMINAL_LOOPSPEED;
				uart_puts("\n");
				uart_puts("Looping Speed CAN Messages \n");
				uart_puts("Type 'c' to exit\n");
				uart_puts("\n");
				return;
				break;

			default:
				// Unknown Command
				uart_puts("\n");
				uart_puts("Unknown command!\n");
				Terminal_showSendMenu();
				uart_puts("\n");
				return;
				break;
			} // Send Command Switch
			break; // Send Submenu

		default:
			// error? No state found ?
			*state = TERMINAL_INIT; // reboot!
			uart_puts("\n");
			uart_puts("Unknown state! Program Crash? :((((\n");
			uart_puts("Attempting reboot \n");
			uart_puts("\n");
			return;
			break;
		} // State Switch
	} // command if

	if(strcasecmp(input, TERMINAL_sCANCEL) == 0){ // Cancel
		*state = TERMINAL_RUN;
		uart_puts("\n");
		uart_puts("Cancelled\n");
		uart_puts("\n");
		Terminal_showMenu();
		return;
	}else{
		uart_puts("\n");
		uart_puts("Sorry I did not understand that, please try again\n");
		uart_puts("\n");
	}





//	else if(strcasecmp(input, TERMINAL_sSEND1) == 0){ // Mode 4
//		*state = TERMINAL_SEND1;
//		uart_puts("\n");
//		uart_puts("Sending MPPT Request \n");
//		uart_puts("\n");
//		return;
//	}
//
//
//
//	else if(strcasecmp(input, TERMINAL_sSENDRANDOM) == 0){ // Mode 6
//		*state = TERMINAL_SENDRANDOM;
//		uart_puts("\n");
//		uart_puts("Sending Random CAN Messages \n");
//		uart_puts("Type 'c' to exit\n");
//		uart_puts("\n");
//		return;
//	}
//	else if(strcasecmp(input, TERMINAL_sSENDBMS) == 0){ // Mode 7
//		*state = TERMINAL_SENDBMS;
//		uart_puts("\n");
//		uart_puts("Sending BMS CAN Messages \n");
//		uart_puts("\n");
//		return;
//	}
//	else if(strcasecmp(input, TERMINAL_sLOOPBMS) == 0){ // Mode 8
//		*state = TERMINAL_LOOPBMS;
//		uart_puts("\n");
//		uart_puts("Looping BMS CAN Messages \n");
//		uart_puts("Type 'c' to exit\n");
//		uart_puts("\n");
//		return;
//	}
//	else if(strcasecmp(input, TERMINAL_sLOOPSPEED) == 0){ // Mode 9
//		*state = TERMINAL_LOOPSPEED;
//		uart_puts("\n");
//		uart_puts("Looping Speed CAN Messages \n");
//		uart_puts("Type 'c' to exit\n");
//		uart_puts("\n");
//		return;
//	}
//
//	else{
//		uart_puts("\n");
//		uart_puts("Sorry I did not understand that, please try again\n");
//
//
//#if defined(DEBUG)
//		uart_puts("String In: ");
//		uart_puts(input);
//		uart_puts("\n");
//		uart_puts("String Help: ");
//		uart_puts(TERMINAL_sHELP);
//		uart_puts("\n");
//#endif
//
//
//		return;
//	}
	return;

}

/*************************************************************************
Function: Terminal_run()
Purpose:  Run the terminal
Input:    state pointer
Returns:  None
**************************************************************************/
void Terminal_run(volatile uint8_t* state){


}

/*************************************************************************
Function: Terminal_showMenu()
Purpose:  Show the main menu
Input:    None
Returns:  None
**************************************************************************/
static void Terminal_showMenu(void){
	uart_puts("\n");
	uart_puts("-------------------------------------\n");
	uart_puts("Main Menu:\n");
	uart_puts("1: Listen Menu\n");
	uart_puts("2: Send Menu\n");
	uart_puts("-------------------------------------\n");
	uart_puts("\n");
	uart_puts("Type 'help' to show this menu again\n");

}

/*************************************************************************
Function: Terminal_showListenMenu()
Purpose:  Show the Listen menu
Input:    None
Returns:  None
**************************************************************************/
static void Terminal_showListenMenu(void){
	uart_puts("\n");
	uart_puts("-------------------------------------\n");
	uart_puts("Listen Menu:\n");
	uart_puts("1: Listen All CAN data Readable\n");
	uart_puts("2: Listen All CAN data Raw\n");
	uart_puts("3: Listen for Specified CAN ID \n");
	uart_puts("0: Go Back to Main Menu \n");
	uart_puts("-------------------------------------\n");
	uart_puts("\n");
	//uart_puts("Type 'help' to show this menu again\n");

}

/*************************************************************************
Function: Terminal_showSendMenu()
Purpose:  Show the Send menu
Input:    None
Returns:  None
**************************************************************************/
static void Terminal_showSendMenu(void){
	uart_puts("\n");
	uart_puts("-------------------------------------\n");
	uart_puts("Send Menu:\n");
	//uart_puts("1: Send Single CAN Message\n");
	//uart_puts("2: Loop Single CAN Message\n");
	uart_puts("3: Send Random CAN Messages\n");
	uart_puts("4: Send BMS CAN Messages\n");
	uart_puts("5: Loop BMS CAN Messages\n");
	uart_puts("6: Loop Speed CAN Messages\n");
	uart_puts("0: Go Back to Main Menu \n");
	uart_puts("-------------------------------------\n");
	uart_puts("\n");
	//uart_puts("Type 'help' to show this menu again\n");

}

