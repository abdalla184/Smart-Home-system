/*
 * MTIMER1_Program.c
 *
 *  Created on: Feb 15, 2022
 *      Author: Dell
 */
#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#include"MTIMER1_Private.h"
#include"MTIMER1_Config.h"


void (*MTIMER1_CALLBACK)(void);

void MTIMER1_VidInit(void)
{
#if TIMER1SETMODE == TIMER1_CTCMODE

	 CLR_BIT(TCCR1A,0);
	 CLR_BIT(TCCR1A,1);
	 SET_BIT(TCCR1B,3);
	 CLR_BIT(TCCR1B,4);
	#if TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_TOGGLEOC1A_OC1BPIN
	 SET_BIT(TCCR1A,4);
	 CLR_BIT(TCCR1A,5);
	 SET_BIT(TCCR1A,6);
	 CLR_BIT(TCCR1A,7);
	#elif TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_SETOC1A_OC1BPIN
	 SET_BIT(TCCR1A,4);
	 SET_BIT(TCCR1A,5);
	 SET_BIT(TCCR1A,6);
	 SET_BIT(TCCR1A,7);
	#elif TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_CLROC1A_OC1BPIN
	 CLR_BIT(TCCR1A,4);
	 SET_BIT(TCCR1A,5);
	 CLR_BIT(TCCR1A,6);
	 SET_BIT(TCCR1A,7);
	#elif TIMER1_CTCMODE_OC1A_OC1BPINMODE== TIMER1_CTCMODE_OC1A_OC1BPIN_NOTCONNECTED
	 CLR_BIT(TCCR1A,4);
	 CLR_BIT(TCCR1A,5);
	 CLR_BIT(TCCR1A,6);
	 CLR_BIT(TCCR1A,7);

	#else
	 #error"OC1A And OC1B Options Is Not Valid.."
	#endif
	/*Compare Match Enable Interrupt*/
	SET_BIT(TIMSK,4);
	SET_BIT(TIMSK,3);

#elif TIMER1SETMODE == TIMER1_NORMALMODE
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	/*OVERFLOW  Enable Interrupt */
	SET_BIT(TIMSK,2);

#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_8_BIT_MODE
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_9_BIT_MODE
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_10_BIT_MODE
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif TIMER1SETMODE==TIMER1_FASTPWM_8_BIT_MODE
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,4);
#elif TIMER1SETMODE==TIMER1_FASTPWM_9_BIT_MODE
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,4);
#elif TIMER1SETMODE==TIMER1_FASTPWM_10_BIT_MODE
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_FREQUENCYCORRECT_MODE_ICR
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
   #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_FREQUENCYCORRECT_MODE_OCR1A
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
   #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_MODE_ICR
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
 #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#elif TIMER1SETMODE==TIMER1_PWMPHASECOORECT_MODE_OCR1A
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3)
	SET_BIT(TCCR1B,4);
  #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#elif TIMER1SETMODE ==TIMER1_CTC_MODE
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
 #if TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_TOGGLEOC1A_OC1BPIN
	SET_BIT(TCCR1A,4);
	CLR_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	CLR_BIT(TCCR1A,7);
 #elif TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_SETOC1A_OC1BPIN
     SET_BIT(TCCR1A,4);
     SET_BIT(TCCR1A,5);
     SET_BIT(TCCR1A,6);
     SET_BIT(TCCR1A,7);
 #elif TIMER1_CTCMODE_OC1A_OC1BPINMODE == TIMER1_CTCMODE_CLROC1A_OC1BPIN
    CLR_BIT(TCCR1A,4);
    SET_BIT(TCCR1A,5);
    CLR_BIT(TCCR1A,6);
    SET_BIT(TCCR1A,7);
 #elif TIMER1_CTCMODE_OC1A_OC1BPINMODE== TIMER1_CTCMODE_OC1A_OC1BPIN_NOTCONNECTED
    CLR_BIT(TCCR1A,4);
    CLR_BIT(TCCR1A,5);
    CLR_BIT(TCCR1A,6);
    CLR_BIT(TCCR1A,7);
 #else
  #error"OC1A And OC1B Options Is Not Valid.."
 #endif
 /*Channel A And B Interrupt Enable */
 	SET_BIT(TIMSK,4);
 	SET_BIT(TIMSK,3);

#elif TIMER1SETMODE==TIMER1_FASTPWM_MODE_ICR
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
 #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#elif TIMER1SETMODE==TIMER1_FASTPWM_MODE_OCR1A
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
 #if TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_NON_INVERTING
	CLR_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #elif TIMER1_PWMMODE_OC1A_OC1B_PINMODE==TIMER1_PWMMODE_INVERTING
	SET_BIT(TCCR1A,4);
	SET_BIT(TCCR1A,5);
	SET_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
   #else
     #error"Channel A And B Options Is Not Valid.."
   #endif

#else
#error "Timer 1 Options Is Not Valid."
#endif

/*********SET PRESCALER *********/
	TCCR1B&=0xF8;
	TCCR1B|=TIMER1_SETPRESCALER;
}
void MTIMER1_VidSetCTCRegister_CHB(uint16 copy_uint16CTCValue)
{
	OCR1B=copy_uint16CTCValue;

}
void MTIMER1_VidSetCTCRegister_CHA(uint16 copy_uint16CTCValue)
{
	OCR1A=copy_uint16CTCValue;

}
void MTIMER1_VidSetCTCRegister_ICR1(uint16 copy_uint16CTCValue)
{
	ICR1=copy_uint16CTCValue;
}
void MTIMER1_VidTimer1_OverFlow_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER1_CALLBACK=PtrToFun;
}
void MTIMER1_VidTimer1_CTC_SetCallBack(void (*PtrToFun)(void))
{
	MTIMER1_CALLBACK=PtrToFun;
}

uint32 MTIMER1_uint32Read_ICR1(void)
{
	return ICR1;
}
void MTIMER1_VidTimer1_ICU_SetCallBack(void(*PtrToFun)(void))
{
	MTIMER1_CALLBACK=PtrToFun;
}
     /*Compare A*/
void __vector_7(void)  __attribute__((signal));
void __vector_7(void)
{
	MTIMER1_CALLBACK();
}
   /*Compare B*/
void __vector_8(void)  __attribute__((signal));
void __vector_8(void)
{
	MTIMER1_CALLBACK();
}
   /*OverFlow */
void __vector_9(void)  __attribute__((signal));
void __vector_9(void)
{
	MTIMER1_CALLBACK();
}
  /*ICU*/
void __vector_6(void)   __attribute__((signal));
void __vector_6(void)
{
	MTIMER1_CALLBACK();
}
