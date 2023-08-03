/*
 * main22.c
 *
 *  Created on: Oct 30, 2021
 *      Author: kirollos Gerges sobhy
 ************************************************************************************************/


/*******************************************************************************
 *                                 Includes                                    *
 *******************************************************************************/
#include "std_types.h"
#include "motor.h"
#include "uart.h"
#include "twi.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "timer0.h"
#include <avr/interrupt.h>
#include <avr/io.h>
uint8 tick=0;/*global value to be 0ne when the timer be 0.25 */
uint8 eeprom[4];/*golabal variable to hold in the eeprom*/
uint8 eepromread[4];/*the global value that read from the eeprom*/
uint8 check1[4];
uint8 ok=0;

/*******************************************************************************
 *                                 functions                                    *
 *******************************************************************************/

void d(){
	tick++;
}
void delay_timer0_normal_mode(uint32 quarter)
{
SetCallBack(d);

	/* Initialize the TIMER0 driver */
config ptr={0,OVER,CLK_1024,INTERRUPT};
	Timer0_init(&ptr);
while(quarter != tick);
tick=0;
DeInit();
}
/**************************************************************
 * description:this function is responsible for putting the password in array
 */
void recieve_the_pass(uint8 * x)
{
	uint8 i=0;
		for(i=0;i<4;i++)
		{
		x[i]=UART_recieveByte();
		delay_timer0_normal_mode(1);
		}
		/**************************************************************
		 * description:this function is responsible for putting the new password in the eeprom
		 */
}
void put_in_eeprom(uint8 * x)
{
	for(uint8 i=0;i<4;i++)
		{
			EEPROM_writeByte(0x0311+i, eeprom[i]); /* Write the password in the external EEPROM */
			delay_timer0_normal_mode(1);
		}
}
/**************************************************************
 * description:this function is responsible for checkin the passwords
 */
void check(void)
{
	uint8 i;
	recieve_the_pass(check1);
	for(i=0;i<4;i++)
{
	EEPROM_readByte(0x0311+i, &(eepromread[i])); /* read the password form the external EEPROM */
	delay_timer0_normal_mode(1);
}
	for( i=0;i<4;i++)
	{
		if(eepromread[i] != check1[i]){
			UART_sendByte(0);
			ok=0;
		}
	}
UART_sendByte(1);
ok=1;
}

int main(void)
{
	/*initialization the uart:
	 * baudrate=9600
	 * diabled the parity
	 * one single stop bit
	 */
	SREG |= (1<<7);
	usart_config ptr={9600,DISABLED,ONE,ASYNC,EIGHT};
	UART_init(&ptr);
	/*initialization twi:
	 * slave address=1
	 * prescaler=1
	 * bit rate division factor=2
	 * */
	TWI_Config p={1,PRE_1,2};
	TWI_init(&p);
	DcMotor_Init();
	buzzer_init();
	while(1)
{
recieve_the_pass(eeprom);
put_in_eeprom(eeprom);
//recieve_the_pass(checkpass);
check();
uint8 button;
button=UART_recieveByte();

if(button==11)
{
	if(ok == 0)
	{
		DcMotor_Rotate(Stop);
	buzzer_on();
	delay_timer0_normal_mode(60);
	buzzer_off();
	}
    else
      {
ok=0;
DcMotor_Rotate(Cw);
delay_timer0_normal_mode(60);
DcMotor_Rotate(Stop);
delay_timer0_normal_mode(8);
DcMotor_Rotate(A_Cw);
delay_timer0_normal_mode(60);
DcMotor_Rotate(Stop);
     }

}
else
{
	if(ok == 0)
		{
		buzzer_on();
		delay_timer0_normal_mode(240);
		buzzer_off();
		}
}

}
return 0;
}


