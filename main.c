/*
 * main.c
 *
 *  Created on: 5 gru 2016
 *      Author: Admin
 */

//===========================================WERSJA 1.0 RELEASE=========================================================
//			UWAGA PROGRAM NAPISANY NA KOLANIE I TAK NAPRAWDÊ WYPADA£O BY GO SKASOWAÆ I NAPISAÆ JESZCZE RAZ

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "mGlobal/mglobal.h"
#include "LCD/lcd44780.h"
#include "mLcdScreenEngineV2/mLcdScreenEngineV2.h"
#include "mKeyboard/mKeyboard.h"
#include "mActuatorAlgorithm/mActuatorAlgorithm.h"

//C_CO PA5 -> Czujnik temperatury

void MCU_INIT( void );

void KeyDn_Handler( void );
void KeyUp_Handler( void );
void KeyMenu_Handler( void );
void KeyExit_Handler( void );

void MenuProcess( void );
void SecondTick( void );

uint8_t menuPos, menuShift = idle, menuStatus = idle;

int main(void){

		MCU_INIT();

//**********************************************************************************************************************

	for(;;){
		ScreenRefresh();

		if( !timer1 ){
			timer1 = 250;
			static uint8_t SubTimer;


			if( !SubTimer ){
				SubTimer = 3;
				SecondTick();
			} else {
//				if( SubTimer == 2 ) LED0_TOG;
				SubTimer--;
			}//end SubTimer

			uint16_t tmp_disp;
			if( ActProcess.stan != disabled ){
				ScrStaticTextLoc( "Cykl:", 7, 0 );
				tmp_disp = ActProcess.cyklCnt;
				ScrVarLoc( &tmp_disp, 13, 0, 3 );


			}

////-----------------------------------------------DEBUG--------------------------------------
//			uint16_t tmp_disp;
//			switch( ActProcess.stan ){
//				case disabled:
//					ScrStaticTextLoc( "d", 15, 0 );
//					break;
//
//				case init:
//					ScrStaticTextLoc( "i", 15, 0 );
//					break;
////
//				case run:
//					ScrStaticTextLoc( "r", 15, 0 );
//					tmp_disp = ActProcess.pracaCnt;
//					ScrVarLoc( &tmp_disp, 14,1,2 );
//
//					break;
//
//				case pause:
//					ScrStaticTextLoc( "p", 15, 0 );
//					tmp_disp = ActProcess.przerwaCnt;
//					ScrVarLoc( &tmp_disp, 14,1,2 );
//					break;
//
//				case stop:
//					ScrStaticTextLoc( "s", 15, 0 );
//					tmp_disp = ActProcess.postojCnt;
//					ScrVarLoc( &tmp_disp, 14,1,2 );
//					break;
//
//
////
//			}
//
//			tmp_disp = ActProcess.cyklCnt;
//			ScrVarLoc(&tmp_disp, 7, 0, 3);
////----------------------------------------END DEBUG------------------------------------------

		}//end timer 1------------------------------------------------------------------------------

		if( !timer2 ){
			timer2 = 10;
			Keyboard_Scan();
		}//end timer 2------------------------------------------------------------------------------

		if( !timer3 ){

			timer3 = 100;

			uint8_t Key0_Status, Key1_Status, Key2_Status, Key3_Status;

			Key0_Status = Keyboard_GetButton0State();
			Key1_Status = Keyboard_GetButton1State();
			Key2_Status = Keyboard_GetButton2State();
			Key3_Status = Keyboard_GetButton3State();

			if( Key0_Status == ButtonPressed_Short ){ KeyDn_Handler(); }
			if( Key1_Status == ButtonPressed_Short ){ KeyUp_Handler(); }
			if( Key2_Status == ButtonPressed_Short ){ KeyMenu_Handler(); }
			if( Key3_Status == ButtonPressed_Short ){ KeyExit_Handler(); }

		}//end timer 3-----------------------------------------------------------------------------

		if( menuStatus == changed ){
			menuStatus = idle;
			MenuProcess();
		}//end menu status-------------------------------------------------------------------------


	}//end for(;;)

}//end main

void MCU_INIT( void ){

	LED0_INIT;
	LED1_INIT;
	LED2_INIT;
	LED3_INIT;
	LCD_BACKLIGHT_INIT;
	LCD_BACKLIGHT_ON;


	_delay_ms( 100 );

//***************************TIMER2*******************************************

	TCCR2A |= ( 1<<WGM21 );  		//CTC
	TCCR2B	|= ( 1<<CS22 ) ;   		//div64
	OCR2A 	|= F_CPU/64UL/1000UL; 	//przerwanie co 1ms - 1kHz		//1ms
	TIMSK2 |= ( 1<<OCIE2A );

//****************************************************************************
	Keyboard_Init();
//****************************************************************************

	lcd_init();

	ScrStaticTextLoc(">---LINIA  0---<", 0, 0);
	ScrStaticTextLoc(">---LINIA  1---<", 0, 1);
	ScreenRefresh();

	LED0_ON;
	_delay_ms( 100 );
	LED1_ON;
	_delay_ms( 100 );
	LED2_ON;
	_delay_ms( 100 );
	LED3_ON;
	_delay_ms( 1000 );

	LED0_OFF;
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;

	P_CO_INIT;
	P_CWU_INIT;

	P_CO_OFF;
	P_CWU_OFF;

	P_CO_OFF;
	P_CWU_OFF;

	RestoreDefault();
	MenuProcess();

	sei();

}//end MCU INIT

void SecondTick( void ){

	switch( ActProcess.stan ){
		case init:
			if(ActProcess.cykl) ActProcess.cyklCnt = ActProcess.cykl - 1; else ActProcess.cyklCnt = 0;
			if(ActProcess.praca) ActProcess.pracaCnt = ActProcess.praca - 1; else ActProcess.pracaCnt = 0;
			if(ActProcess.przerwa) ActProcess.przerwaCnt = ActProcess.przerwa - 1; else ActProcess.przerwaCnt = 0;
			if(ActProcess.postoj) ActProcess.postojCnt = ActProcess.postoj - 1; else ActProcess.postojCnt = 0;

			ActProcess.stan = run;
			break;

		case enabled:
			break;

		case disabled:
			P_CO_OFF;
			P_CWU_OFF;

			break;

		case run:
			if( ActProcess.pracaCnt ){
				ActProcess.pracaCnt--;
				if( ActProcess.kierunek == left ){P_CO_ON; P_CWU_OFF;} else {P_CO_OFF; P_CWU_ON;}

				if( ActProcess.cyklCnt ){

					ActProcess.cyklCnt--;

				} else {
					ActProcess.stan = stop;
					if(ActProcess.postoj) ActProcess.postojCnt = ActProcess.postoj-1; else ActProcess.postojCnt = 0;

					P_CO_OFF;
					P_CWU_OFF;

					if( ActProcess.kierunek == left ) ActProcess.kierunek = right; else ActProcess.kierunek = left;
				}

			} else {
				ActProcess.stan = pause;
				if(ActProcess.praca) ActProcess.pracaCnt = ActProcess.praca - 1; else ActProcess.pracaCnt = 0;
			}
			break;

		case pause:
			if( ActProcess.przerwaCnt ){
				ActProcess.przerwaCnt--;
				P_CO_OFF;
				P_CWU_OFF;
			} else {
				ActProcess.stan = run;
				if(ActProcess.przerwa) ActProcess.przerwaCnt = ActProcess.przerwa - 1; else ActProcess.przerwaCnt = 0;

			}
			break;

		case stop:
			if( ActProcess.postojCnt ){
				ActProcess.postojCnt--;
			} else {
				ActProcess.cyklCnt = ActProcess.cykl;
				ActProcess.stan = run;
				if(ActProcess.praca) ActProcess.pracaCnt = ActProcess.praca - 1; else ActProcess.pracaCnt = 0;
			}

			break;

	}

}

//------------------Obs³uga klawiszy-------------------
void KeyUp_Handler( void ){
	if( (menuPos > 0) && ( menuShift == idle ) ){
		menuPos--;
	}

	if( menuShift == shifted ){

		switch(menuPos){

		case 0:
			break;

		case 1:
			ActProcess.praca++;
			break;

		case 2:
			ActProcess.przerwa++;
			break;

		case 3:
			ActProcess.cykl++;
			break;

		case 4:
			ActProcess.postoj++;
			break;

		case 5:
			break;


		}

	}//-----------------------------------------

	menuStatus = changed;
}

void KeyDn_Handler( void ){
	if( (menuPos < 6) && (menuShift == idle) ){
		menuPos++;
	}

	if( menuShift == shifted ){

		switch(menuPos){

		case 0:
			break;

		case 1:
			if(ActProcess.praca > 2) ActProcess.praca--;
			break;

		case 2:
			if(ActProcess.przerwa > 2) ActProcess.przerwa--;
			break;

		case 3:
			if(ActProcess.cykl > 2) ActProcess.cykl--;
			break;

		case 4:
			if(ActProcess.postoj > 2) ActProcess.postoj--;
			break;

		case 5:

			break;


		}
	}//-----------------------------------------

	menuStatus = changed;

}

void KeyMenu_Handler( void ){
	if( menuShift == idle ) {menuShift = shifted;} else {menuShift = idle;}
	menuStatus = changed;

}

void KeyExit_Handler( void ){
	menuStatus = changed;
}

void MenuProcess( void ){

	uint16_t tmp;
		if( menuShift == idle ){
			switch( menuPos ){

			case 0:
				ScrStaticTextLoc(">Start          ", 0, 0);
				ScrStaticTextLoc(" Praca:         ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 1, 2);

				ActProcess.stan = disabled;

				break;

			case 1:

				ScrStaticTextLoc(" Start          ", 0, 0);
				ScrStaticTextLoc(">Praca:         ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 1, 2);

				break;

			case 2:
				ScrStaticTextLoc(" Praca:         ", 0, 0);
				ScrStaticTextLoc(">Przerwa:       ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 0, 2);

				tmp = ActProcess.przerwa;
				ScrVarLoc( &tmp, 11, 1, 2);

				break;

			case 3:
				ScrStaticTextLoc(" Przerwa:       ", 0, 0);
				ScrStaticTextLoc(">Cykl:          ", 0, 1);

				tmp = ActProcess.przerwa;
				ScrVarLoc( &tmp, 11, 0, 2);

				tmp = ActProcess.cykl;
				ScrVarLoc( &tmp, 11, 1, 3);

				break;

			case 4:
				ScrStaticTextLoc(" Cykl:          ", 0, 0);
				ScrStaticTextLoc(">Postoj:        ", 0, 1);

				tmp = ActProcess.cykl;
				ScrVarLoc( &tmp, 11, 0, 3);

				tmp = ActProcess.postoj;
				ScrVarLoc( &tmp, 11, 1, 2);
				break;

			case 5:
				ScrStaticTextLoc(" Postoj         ", 0, 0);
				ScrStaticTextLoc(">Zapisz ustaw.  ", 0, 1);

				tmp = ActProcess.postoj;
				ScrVarLoc( &tmp, 11, 0, 2);

				break;
			}//-----------------------------endswitch-------------------
		}//----------------------endif-----------------------------------

		if( menuShift == shifted ){
			switch( menuPos ){

			case 0:
				ScrStaticTextLoc(">Stop           ", 0, 0);
				ScrStaticTextLoc(" Praca:         ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 1, 2);
				ActProcess.stan = init;

				break;

			case 1:

				ScrStaticTextLoc(" Start          ", 0, 0);
				ScrStaticTextLoc(" Praca:   >     ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 1, 2);

				break;

			case 2:
				ScrStaticTextLoc(" Praca:         ", 0, 0);
				ScrStaticTextLoc(" Przerwa: >     ", 0, 1);

				tmp = ActProcess.praca;
				ScrVarLoc( &tmp, 11, 0, 2);

				tmp = ActProcess.przerwa;
				ScrVarLoc( &tmp, 11, 1, 2);

				break;

			case 3:
				ScrStaticTextLoc(" Przerwa:       ", 0, 0);
				ScrStaticTextLoc(" Cykl:    >     ", 0, 1);

				tmp = ActProcess.przerwa;
				ScrVarLoc( &tmp, 11, 0, 2);

				tmp = ActProcess.cykl;
				ScrVarLoc( &tmp, 11, 1, 3);

				break;

			case 4:
				ScrStaticTextLoc(" Cykl:          ", 0, 0);
				ScrStaticTextLoc(" Postoj:  >     ", 0, 1);

				tmp = ActProcess.cykl;
				ScrVarLoc( &tmp, 11, 0, 3);

				tmp = ActProcess.postoj;
				ScrVarLoc( &tmp, 11, 1, 2);
				break;

			case 5:
				ScrStaticTextLoc(" Postoj         ", 0, 0);
				ScrStaticTextLoc(">Zapisz ustaw.  ", 0, 1);

				tmp = ActProcess.postoj;
				ScrVarLoc( &tmp, 11, 0, 2);

				break;


			}


		}

}
//----------------------------------------------------

ISR( TIMER2_COMPA_vect ){

	static uint8_t n;

	n = timer1;
	if (n)
		timer1 = --n;

	n = timer2;
	if (n)
		timer2 = --n;

	n = timer3;
	if (n)
		timer3 = --n;

	n = timer4;
	if (n)
		timer4 = --n;

}//end ISR TIMER2_COMP_vect
