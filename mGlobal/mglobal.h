/*
 * mglobal.h
 *
 *  Created on: 28 mar 2016
 *      Author: Zygmunt
 */

#ifndef MGLOBAL_MGLOBAL_H_
#define MGLOBAL_MGLOBAL_H_

volatile uint8_t timer1, timer2, timer3, timer4;			//timer1 .. 4 - liczniki programowe

enum States{low, high, rising, falling, idle, changed, shifted, left, right, up, down, enabled, disabled, run, stop, pause, init};

#define PORT(x)		XPORT(x)
#define XPORT(x)	(PORT##x)

#define PIN(x)		XPIN(x)
#define XPIN(x)		(PIN##x)

#define DDR(x)		XDDR(x)
#define XDDR(x)		(DDR##x)

//=============================INDICATOR LED================================

#define LED0_PORT B
#define LED0_PIN  0

#define LED1_PORT A
#define LED1_PIN  0

#define LED2_PORT A
#define LED2_PIN  2

#define LED3_PORT A
#define LED3_PIN  3

//***************************************************************************

#define PWM1_OUT_PORT D
#define PWM1_OUT_PIN  6

#define PWM2_OUT_PORT D
#define PWM2_OUT_PIN  5

#define RELAY0_PORT	B
#define RELAY0_PIN	7

#define MovSensorIn_PORT C
#define MovSensorIn_PIN	 5

#define P_CO_PORT C
#define P_CO_PIN 4

#define P_CWU_PORT C
#define P_CWU_PIN 3

//-------------------------------------------------------------------

#define PORT(x)		XPORT(x)
#define XPORT(x)	(PORT##x)

#define PIN(x)		XPIN(x)
#define XPIN(x)		(PIN##x)

#define DDR(x)		XDDR(x)
#define XDDR(x)		(DDR##x)

//--------------------------------LEDS--------------------------------------

#define LED0_INIT 	DDR(LED0_PORT) 	|= ( 1<<PIN(LED0_PIN) )
#define LED0_ON		PORT(LED0_PORT)	|= ( 1<<PIN(LED0_PIN) )
#define LED0_OFF  	PORT(LED0_PORT)	&= ~( 1<<PIN(LED0_PIN) )
#define LED0_TOG	PORT(LED0_PORT)	^= ( 1<<PIN(LED0_PIN) )

#define LED1_INIT 	DDR(LED1_PORT) 	|= ( 1<<PIN(LED1_PIN) )
#define LED1_ON		PORT(LED1_PORT)	|= ( 1<<PIN(LED1_PIN) )
#define LED1_OFF  	PORT(LED1_PORT)	&= ~( 1<<PIN(LED1_PIN) )
#define LED1_TOG	PORT(LED1_PORT)	^= ( 1<<PIN(LED1_PIN) )

#define LED2_INIT 	DDR(LED2_PORT) 	|= ( 1<<PIN(LED2_PIN) )
#define LED2_ON		PORT(LED2_PORT)	|= ( 1<<PIN(LED2_PIN) )
#define LED2_OFF  	PORT(LED2_PORT)	&= ~( 1<<PIN(LED2_PIN) )
#define LED2_TOG	PORT(LED2_PORT)	^= ( 1<<PIN(LED2_PIN) )

#define LED3_INIT 	DDR(LED3_PORT) 	|= ( 1<<PIN(LED3_PIN) )
#define LED3_ON		PORT(LED3_PORT)	|= ( 1<<PIN(LED3_PIN) )
#define LED3_OFF  	PORT(LED3_PORT)	&= ~( 1<<PIN(LED3_PIN) )
#define LED3_TOG	PORT(LED3_PORT)	^= ( 1<<PIN(LED3_PIN) )

//--------------------------------------------------------------------------

#define PWM1_OUT_INIT 	DDR(PWM1_OUT_PORT) 	|= ( 1<<PIN(PWM1_OUT_PIN) )
#define PWM1_OUT_ON  	PORT(PWM1_OUT_PORT)	&= ~( 1<<PIN(PWM1_OUT_PIN) )
#define PWM1_OUT_OFF	PORT(PWM1_OUT_PORT)	|= ( 1<<PIN(PWM1_OUT_PIN) )
#define PWM1_OUT_TOG	PORT(PWM1_OUT_PORT)	^= ( 1<<PIN(PWM1_OUT_PIN) )

#define PWM2_OUT_INIT 	DDR(PWM2_OUT_PORT) 	|= ( 1<<PIN(PWM2_OUT_PIN) )
#define PWM2_OUT_ON		PORT(PWM2_OUT_PORT)	|= ( 1<<PIN(PWM2_OUT_PIN) )
#define PWM2_OUT_OFF  	PORT(PWM2_OUT_PORT)	&= ~( 1<<PIN(PWM2_OUT_PIN) )
#define PWM2_OUT_TOG	PORT(PWM2_OUT_PORT)	^= ( 1<<PIN(PWM2_OUT_PIN) )

//-----------------------------------------------------------------

#define RELAY0_INIT DDR(RELAY0_PORT) 	|= ( 1<<PIN(RELAY0_PIN) )
#define RELAY0_ON	PORT(RELAY0_PORT)	|= ( 1<<PIN(RELAY0_PIN) )
#define RELAY0_OFF  PORT(RELAY0_PORT)	&= ~( 1<<PIN(RELAY0_PIN) )
#define RELAY0_TOG	PORT(RELAY0_PORT)	^= ( 1<<PIN(RELAY0_PIN) )

//------------------------------------------------------------------

#define MovSensorIn_INIT	DDR(MovSensorIn_PORT) 	&= ~( 1<<PIN(MovSensorIn_PIN) )
#define MovSensorIn_PULL	PORT(MovSensorIn_PORT) 	|=  ( 1<<PIN(MovSensorIn_PIN) )
#define MovSensorIn_NOPULL	PORT(MovSensorIn_PORT) 	&= ~( 1<<PIN(MovSensorIn_PIN) )

#define MovSensorIn_PRESS   !(PIN(MovSensorIn_PORT) & ( 1<<MovSensorIn_PIN ))
#define MovSensorIn_RELIEF   (PIN(MovSensorIn_PORT) & ( 1<<MovSensorIn_PIN ))

//------------------------------------------------------------------

#define P_CO_INIT 	DDR(P_CO_PORT) 	|= ( 1<<PIN(P_CO_PIN) )
#define P_CO_ON		(PORT(P_CO_PORT)	|= ( 1<<PIN(P_CO_PIN) )); LED2_ON;
#define P_CO_OFF  	(PORT(P_CO_PORT)	&= ~( 1<<PIN(P_CO_PIN) )); LED2_OFF;
#define P_CO_TOG	(PORT(P_CO_PORT)	^= ( 1<<PIN(P_CO_PIN) )); LED2_TOG;

//------------------------------------------------------------------

#define P_CWU_INIT 	DDR(P_CWU_PORT) 	|= ( 1<<PIN(P_CWU_PIN) )
#define P_CWU_ON	(PORT(P_CWU_PORT)	|= ( 1<<PIN(P_CWU_PIN) )); LED1_ON;
#define P_CWU_OFF  	(PORT(P_CWU_PORT)	&= ~( 1<<PIN(P_CWU_PIN) )); LED1_OFF;
#define P_CWU_TOG	(PORT(P_CWU_PORT)	^= ( 1<<PIN(P_CWU_PIN) )); LED1_TOG;

//=================================================================

//Opis timerów programowych, taktowanych timerem sprzêtowym: Timer 2

//timer1 -
//timer2 -
//timer3 -
//timer4 -

#endif /* MGLOBAL_MGLOBAL_H_ */
