
/*
 * main.c
 *
 *  Created on: Oct 30, 2021
 *      Author: kirollos Gerges sobhy
 ************************************************************************************************/
/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "lcd.h"
#include "std_types.h"
#include "keypad.h"
#include "uart.h"
uint8 pass1[4];//the password
uint8 tick =0;

/*******************************************************************************
 *                                 functions                                    *
 *******************************************************************************/



/******************************************************************************
 * description:this function is responsible for the delay
 **/
void d(){
	tick++;
}
void delay_timer0_normal_mode(uint32 quarter)
{
SetCallBack(d);

	/* Initialize the TIMER0 driver */
config ptr={0,OVER,5,INTERRUPT};
	Timer0_init(&ptr);
while(quarter != tick);
tick=0;
DeInit();
}
void getpassword()
{
	LCD_clearScreen();
	uint8 i=0;
	LCD_displayString("enter 1password");
	LCD_moveCursor(1,0);
	for( i=0;i<4;i++){
	//delay_timer0_normal_mode(1);
	pass1[i]=KEYPAD_getPressedKey();
	LCD_intgerToString(pass1[i]);
	delay_timer0_normal_mode(2);
	}
}
/******************************************************************************
 * description:this function is responsible for sending the password to the mc2
 **/
 send_the_pass()
{
	uint8 i=0;
	for(i=0;i<4;i++)
	{
	UART_sendByte(pass1[i]);
	delay_timer0_normal_mode(1);
	}
}
 /******************************************************************************
  * description:this function is responsible for reentering the password
  **/
uint8 reenter_password()
{
	LCD_clearScreen();
	uint8 i=0;
	uint8 pass2[4];
	LCD_displayString("re enter: ");
	LCD_moveCursor(1,0);
	for( i=0;i<4;i++){
	pass2[i]=KEYPAD_getPressedKey();
	LCD_intgerToString(pass2[i]);
	delay_timer0_normal_mode(2);
	}
	for(uint8 i=0;i<4;i++)
	{
		if(pass1[i]!=pass2[i])
		{
			return 0;

		}

}
LCD_clearScreen();
LCD_displayString("ok");
delay_timer0_normal_mode(2);
return 1;
}

/******************************************************************************
 * description:this function is responsible for the last compare before sending the password to the microcontroll
 **/


void fullcompare()
{
	uint8 check=0;
	getpassword();
	check=reenter_password();
	while(!check){
					LCD_clearScreen();
					getpassword();
					delay_timer0_normal_mode(1);
					reenter_password();
				}
				send_the_pass(pass1);
				delay_timer0_normal_mode(1);
}
int main(void)
{
	SREG |= (1<<7);
	LCD_init();
	usart_config ptr={9600,DISABLED,ONE,ASYNC,EIGHT};
	UART_init(&ptr);
	fullcompare();
	while(1)
    {
LCD_clearScreen();
LCD_displayString("+:open the door");
LCD_moveCursor(1, 0);
LCD_displayString("-:change pass");
if(KEYPAD_getPressedKey()=='+')
{
	delay_timer0_normal_mode(2);
	LCD_clearScreen();
	uint8 check=0;
	getpassword();
	send_the_pass(pass1);
	check = UART_recieveByte();
	delay_timer0_normal_mode(2);
	UART_sendByte(11);
	if(check==1)
	{
		LCD_clearScreen();
		LCD_displayString("openning");
		delay_timer0_normal_mode(60);
		LCD_clearScreen();
		LCD_displayString("opened");
		delay_timer0_normal_mode(8);
		LCD_clearScreen();
		LCD_displayString("closing");
		delay_timer0_normal_mode(60);
		LCD_clearScreen();
    }
	else
	{
	LCD_clearScreen();
	LCD_displayString("wrong");
	delay_timer0_normal_mode(60);
	LCD_clearScreen();
	}
	}
if(KEYPAD_getPressedKey()=='-')
{
uint8 check2=0;
LCD_clearScreen();
getpassword();
send_the_pass(pass1);
check2 =UART_recieveByte();
delay_timer0_normal_mode(1);
UART_sendByte(22);
if(check2==1)
{
	fullcompare();
}
else
{
	LCD_clearScreen();
	LCD_displayString("wrong");
	delay_timer0_normal_mode(240);
	LCD_clearScreen();
}

}
    }
return 0;
}
