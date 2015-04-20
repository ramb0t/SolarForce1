/*
 * main.c
 *
 *  Created on: 26 Feb 2015
 *      Author: RobThePyro
 */


/*
lcdpcf8574 lib sample

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include "main.h"

int main(void)
{

	SPI_Init();
	mcp2515_init();
	// Create a new message
	CANMessage message;
	uint8_t rx_status = 0xff;


	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    sei();

    //init lcd
    lcd_init(LCD_DISP_ON);

    //lcd go home
    lcd_home();

    uint8_t led = 0;

    while(1) {
    	rx_status = can_get_message (&message); //gets msg from bus (pointer to the object of CanMessage type) [returns value based on result of Rx
    	lcd_led(led); //set led
    	//led = !led; //invert led for next loop

    	//test loop
//    	int i = 0;
//    	int line = 0;
//    	for(i=0; i<10; i++) {
//    		char buf[10];
//    		itoa(i, buf, 10);
//    		lcd_gotoxy(0, line);
//    		lcd_puts("i= ");
//    		lcd_gotoxy(3, line);
//    		lcd_puts(buf);
//    		line++;
//    		line %= 2;
//        	uart_puts(buf);
//        	uart_puts("\r\n");
//    		_delay_ms(500);
//    	}

    	if(rx_status!=0xff){
    		lcd_clrscr();
    			// we have a message now!!
    		char buf[10]; // used for forming strings to pass to the display ??

    		// ID
    		itoa(message.id, buf, 10);
    		lcd_gotoxy(0, 0);
    		lcd_puts("ID= ");
    		lcd_gotoxy(4, 0);
    		lcd_puts(buf);
    		uart_puts("ID= ");
    		uart_puts(buf);

    		// L
    		itoa(message.length, buf, 10);
    		lcd_gotoxy(15, 0);
    		lcd_puts("L= ");
    		lcd_gotoxy(18, 0);
    		lcd_puts(buf);
    		uart_puts("; Length= ");
    		uart_puts(buf);

    		// D0
    		if(message.length > 0){
				itoa(message.data[0], buf, 10);
				lcd_gotoxy(0, 1);
				lcd_puts("D0= ");
				lcd_gotoxy(3, 1);
				lcd_puts(buf);
				uart_puts("; D0= ");
				uart_puts(buf);
    		}
    		// D1
    		if(message.length > 1){
				itoa(message.data[1], buf, 10);
				lcd_gotoxy(7, 1);
				lcd_puts("D1= ");
				lcd_gotoxy(10, 1);
				lcd_puts(buf);
				uart_puts("; D1= ");
				uart_puts(buf);
    		}
    		// D2
    		if(message.length > 2){
				itoa(message.data[2], buf, 10);
				lcd_gotoxy(14, 1);
				lcd_puts("D0= ");
				lcd_gotoxy(17, 1);
				lcd_puts(buf);
				uart_puts("; D2= ");
				uart_puts(buf);
    		}
    		// D3
    		if(message.length > 3){
				itoa(message.data[3], buf, 10);
				lcd_gotoxy(0, 2);
				lcd_puts("D3= ");
				lcd_gotoxy(3, 2);
				lcd_puts(buf);
				uart_puts("; D3= ");
				uart_puts(buf);
    		}
    		// D4
    		if(message.length > 4){
				itoa(message.data[4], buf, 10);
				lcd_gotoxy(7, 2);
				lcd_puts("D4= ");
				lcd_gotoxy(10, 2);
				lcd_puts(buf);
				uart_puts("; D4= ");
				uart_puts(buf);
    		}
    		// D5
    		if(message.length > 5){
				itoa(message.data[5], buf, 10);
				lcd_gotoxy(14, 2);
				lcd_puts("D5= ");
				lcd_gotoxy(17, 2);
				lcd_puts(buf);
				uart_puts("; D5= ");
				uart_puts(buf);
    		}
    		// D6
    		if(message.length > 6){
				itoa(message.data[6], buf, 10);
				lcd_gotoxy(0, 3);
				lcd_puts("D6= ");
				lcd_gotoxy(3, 3);
				lcd_puts(buf);
				uart_puts("; D6= ");
				uart_puts(buf);
    		}
    		// D7
    		if(message.length > 7){
				itoa(message.data[7], buf, 10);
				lcd_gotoxy(7, 3);
				lcd_puts("D7= ");
				lcd_gotoxy(10, 3);
				lcd_puts(buf);
				uart_puts("; D7= ");
				uart_puts(buf);
    		}
    		//    		line %= 2;
    		//uart_puts(buf);
    		uart_puts("\r\n");
    		//    		_delay_ms(500);
    			// check if valid?
    			//if (message.data[0] == 0x04 )
    			//	{
    			//		if(message.data[1]==0x01){
    			//		PORTB |= (1<<PORTB1);}
    			//		else if(message.data[1]==0x02){
    			//		PORTB &=~(1<<PORTB1);}
    			//		_delay_ms(200);
    			//	}


    		}
    }
}

