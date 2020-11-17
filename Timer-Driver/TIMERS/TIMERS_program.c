/***********************************************************/
/***************  Name   : Mahmoud .R **********************/
/***************  Date   : 22/9/2020  **********************/
/***************  SWC    : TIMERS     **********************/
/*************** Version : 1.0        **********************/
/***********************************************************/  
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h"

/* Global Pointer to Function of Timer0 OVF */
static void(*TIMERS_pfTimer0OVF)(void) = NULL;
static void(*TIMERS_pfTimer0CTC)(void) = NULL;

void TIMERS_voidTimer0Init(void)
{
//	/* Select Mode => Normal Mode */
//	/*	CLR_BIT(TIMERS_u8_TCCR0_REG,6);
//	CLR_BIT(TIMERS_u8_TCCR0_REG,3);*/
//
//	/* Select Mode => CTC Mode */
//	CLR_BIT(TIMERS_u8_TCCR0_REG,6);
//	SET_BIT(TIMERS_u8_TCCR0_REG,3);
//
//	/* Enable OVF Interrupt */
//	//SET_BIT(TIMERS_u8_TIMSK_REG,0);
//	/* Enable CTC Interrupt */
//	SET_BIT(TIMERS_u8_TIMSK_REG,1);
//	/*SEt compare match unit register*/
//	TIMERS_u8_OCR0_REG = 99;
//	/* Set Preload Value */
//	//TIMERS_u8_TCNT0_REG = 192;
//	/* Set Prescaler Value CLK/8 */
//	CLR_BIT(TIMERS_u8_TCCR0_REG,2);
//	SET_BIT(TIMERS_u8_TCCR0_REG,1);
//	CLR_BIT(TIMERS_u8_TCCR0_REG,0);

//	/* Select Mode => Fast PWM Mode */
//	SET_BIT(TIMERS_u8_TCCR0_REG,6);
//	SET_BIT(TIMERS_u8_TCCR0_REG,3);
//	/* Select HW Action On OC0Pin => Non Inverting */
//	SET_BIT(TIMERS_u8_TCCR0_REG,5);
//	CLR_BIT(TIMERS_u8_TCCR0_REG,4);
//	/* Set Prescaler Value CLK/8 */
//	CLR_BIT(TIMERS_u8_TCCR0_REG,2);
//	SET_BIT(TIMERS_u8_TCCR0_REG,1);
//	CLR_BIT(TIMERS_u8_TCCR0_REG,0);


	/* Select Mode => Phase correct PWM Mode */
	CLR_BIT(TIMERS_u8_TCCR0_REG,6);
	SET_BIT(TIMERS_u8_TCCR0_REG,3);
	/* Select HW Action On OC0Pin => Non Inverting */
	SET_BIT(TIMERS_u8_TCCR0_REG,5);
	CLR_BIT(TIMERS_u8_TCCR0_REG,4);
	/* Set Prescaler Value CLK/8 */
	CLR_BIT(TIMERS_u8_TCCR0_REG,2);
	SET_BIT(TIMERS_u8_TCCR0_REG,1);
	CLR_BIT(TIMERS_u8_TCCR0_REG,0);
}

void TIMERS_voidTimer1Init(void)
{
//	/* Select Timer1 Mode => 14 ICR1 = Top Value*/
//	SET_BIT(TIMERS_u8_TCCR1A_REG,1);
//	CLR_BIT(TIMERS_u8_TCCR1A_REG,0);
//	SET_BIT(TIMERS_u8_TCCR1B_REG,4);
//	SET_BIT(TIMERS_u8_TCCR1B_REG,3);
//
//	/* Select HW Action on OC1A pin => Non Inverting */
//	SET_BIT(TIMERS_u8_TCCR1A_REG,7);
//	CLR_BIT(TIMERS_u8_TCCR1A_REG,6);
//
//	/* Set Top Value in ICR1 */
//	TIMERS_u16_ICR1_REG = 19999;
//
//	/* Set Angle of Servo Motor */
//	TIMERS_u16_OCR1A_REG = 499;
//
//	/* Set Prescaler Value CLK/8 */
//	CLR_BIT(TIMERS_u8_TCCR1B_REG,2);
//	SET_BIT(TIMERS_u8_TCCR1B_REG,1);
//	CLR_BIT(TIMERS_u8_TCCR1B_REG,0);

	/* Select mode of Timer1 = Normal Mode */
	CLR_BIT(TIMERS_u8_TCCR1A_REG,1);
	CLR_BIT(TIMERS_u8_TCCR1A_REG,0);
	CLR_BIT(TIMERS_u8_TCCR1A_REG,4);
	CLR_BIT(TIMERS_u8_TCCR1A_REG,3);

	/* Starts Timer1 at Prescaler 8 */
	CLR_BIT(TIMERS_u8_TCCR1B_REG,2);
	SET_BIT(TIMERS_u8_TCCR1B_REG,1);
	CLR_BIT(TIMERS_u8_TCCR1B_REG,0);
}

void TIMER_voidTimer0SetCompareMatchValue(u8 Copy_u8OCR0Value)
{
  TIMERS_u8_OCR0_REG = Copy_u8OCR0Value;
}

void TIMER_voidTimer1SetCompareMatchValue(u16 Copy_u16OCR1Value)
{
  TIMERS_u16_OCR1A_REG = Copy_u16OCR1Value;
}

u8   TIMERS_u8Timer0SetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0OVF =Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8   TIMERS_u8Timer0CTCSetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0CTC =Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

/* Prototype for ISR of TIMER0 OVF */
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	static u16 Local_u16OCounterOVF = 0;
	Local_u16OCounterOVF++;
	if(Local_u16OCounterOVF == 3907)
	{
		/* UpdatePreload Value */
	    TIMERS_u8_TCNT0_REG = 192;		
		/* Clear the OVF Counter */
		Local_u16OCounterOVF = 0;
		/* Call App function */
		if(TIMERS_pfTimer0OVF != NULL)
		{
			TIMERS_pfTimer0OVF();
		}
	}
}

/* Prototype for ISR of TIMER0 CTC */
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	static u16 Local_u16OCounterCTC = 0;
	Local_u16OCounterCTC++;
	if(Local_u16OCounterCTC == 10000)
	{
      /* Clear CounterCTC = 0 */
		Local_u16OCounterCTC = 0;
		/* Call CallBack  function*/
		if(TIMERS_pfTimer0CTC != NULL)
		{
			TIMERS_pfTimer0CTC();
		}
	}
}
