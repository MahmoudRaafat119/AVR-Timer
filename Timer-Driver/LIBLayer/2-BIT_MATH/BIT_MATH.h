/***********************************************************/
/***************  Name   : Mahmoud .R **********************/
/***************  Date   : 27/8/2020  **********************/
/***************  SWC    : DIO        **********************/
/*************** Version : 1.0        **********************/
/***********************************************************/
#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)


#endif
