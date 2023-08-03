/*
 * timer0.h
 *
 *  Created on: Oct 26, 2021
 *      Author: kirollos gerges sobhy
 *********************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include"std_types.h"

/******************************************************
 *             the configration
 ****************************************************/

typedef enum
{
	INTERRUPT , POLLING
}interfacing_type;
typedef enum
{
  OVER,COMPARE
}mode;
typedef enum
{
	CLK=1,CLK_8,CLK_64,CLK_256,CLK_1024=5
}prescaler;

typedef struct
{
uint8 OCROO;
mode MODE;
prescaler PRESCALER;
interfacing_type TYPE;

}config;



/************************************************
 *                    FUNCTIONS DIFINATIONS
 ***********************************************/


/*
 * function that initialize the timer
 */
void Timer0_init(const config * ptr);

/*
 * function to de-initialize the timer
 */
void DeInit();

/*
 * setting call back function
 */
void SetCallBack(void(*a_ptr)(void));








#endif /* TIMER0_H_ */
