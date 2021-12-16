/*
 * mActuatorAlgorithm.c
 *
 *  Created on: 3 wrz 2021
 *      Author: user
 */
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../mGlobal/mglobal.h"
#include "mActuatorAlgorithm.h"
#include "avr/eeprom.h"

T_ACT_PROCESS ActProcess;
T_ACT_PROCESS EEMEM ActProcess_EEMEM;

void RestoreDefault( void ){

	ActProcess.cykl = 150;
	ActProcess.praca = 10;
	ActProcess.przerwa = 10;
	ActProcess.postoj = 10;
	ActProcess.kierunek = left;

	ActProcess.stan = disabled;

}

void RestoreSetings_E( void ){

//	ActProcess.cykl = 150;
//	ActProcess.praca = 10;
//	ActProcess.przerwa = 10;
//	ActProcess.postoj = 10;
//	ActProcess.kierunek = left;
//
//	ActProcess.stan = disabled;
	cli();

	if( eeprom_is_ready() ){

		eeprom_read_block( &ActProcess, &ActProcess_EEMEM, sizeof(ActProcess) );

	}

	sei();
}

void SaveSetings_E( void ){
	cli();

//EEP Save block
	if( eeprom_is_ready() )	{

		eeprom_write_block( &ActProcess, &ActProcess_EEMEM, sizeof(ActProcess) );
		eeprom_busy_wait();

	}
//	_delay_ms(25);
	sei();

}
