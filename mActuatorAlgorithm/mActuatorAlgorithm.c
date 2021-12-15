/*
 * mActuatorAlgorithm.c
 *
 *  Created on: 3 wrz 2021
 *      Author: user
 */
#include <avr/io.h>
#include "../mGlobal/mglobal.h"
#include "mActuatorAlgorithm.h"

T_ACT_PROCESS ActProcess;

void RestoreDefault( void ){

	ActProcess.cykl = 150;
	ActProcess.praca = 10;
	ActProcess.przerwa = 10;
	ActProcess.postoj = 10;
	ActProcess.kierunek = left;

	ActProcess.stan = disabled;

}
