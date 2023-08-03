/*
 *

 *  Created on: Oct 30, 2021
 *      Author: kirollos gerges sobhy
 *********************************************************************************/
/*******************************************************
 *            includes
 *******************************************************/
#include "timer0.h"
#include "common_macros.h"
#include <avr/io.h>
#include<avr/interrupt.h>

/*
 * the call back pointer
 * */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * ISR in case of OVERFLOW mood
 */
/*************************************************************
 * functions
 *******************************************/


/*
 * DESCRIPTION: the function is to stop the timer
 */
void  DeInit(void)
{

	TCCR0 = 0;
}




/*
 * function that initialize the timer
 */
void  Timer0_init(const const config * ptr)
{
	SREG |=(1<<7);
	TCNT0=0;  // intialize the timer
	TCCR0|=(1<<FOC0);
	if(ptr->MODE==COMPARE)
	{
		OCR0  = ptr->OCROO; // Set Compare Value
		TCCR0 |=(1<<WGM01);
		if (ptr->TYPE == INTERRUPT)
		{

			TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		}

	}

	else if((ptr->MODE==OVER) && (ptr->TYPE == INTERRUPT))
	{



		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt

	}
	TCCR0 = (TCCR0&0xf8)|(ptr->PRESCALER);//setting the prescaler


	if (ptr->TYPE == POLLING)
	{
		if(ptr->MODE==OVER)
		{
			while(!(TIFR & (1<<TOV0))); // Wait until the FLAG
		}
		else if (ptr->MODE==COMPARE)
		{
			while(!(TIFR & (1<<OCF0))); // Wait until the FLAG
		}
		DeInit();
	}




}
/****************************************************
 * the normal mode isr
 * ******************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * ISR in Compare mood
 */

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


/*
 * setting call back function
 */
void SetCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}


