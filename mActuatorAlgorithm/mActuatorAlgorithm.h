/*
 * mActuatorAlgorithm.h
 *
 *  Created on: 3 wrz 2021
 *      Author: user
 */

#ifndef MACTUATORALGORITHM_MACTUATORALGORITHM_H_
#define MACTUATORALGORITHM_MACTUATORALGORITHM_H_

typedef struct T_ACT_PROCESS{

	uint16_t cykl;
	uint8_t praca;
	uint8_t przerwa;
	uint8_t postoj;

	uint16_t cyklCnt;
	uint8_t pracaCnt;
	uint8_t przerwaCnt;
	uint8_t postojCnt;

	uint8_t kierunek;

	uint8_t stan;

}T_ACT_PROCESS;


T_ACT_PROCESS ActProcess;
T_ACT_PROCESS ActProcess_EEMEM;

void RestoreDefault( void );
void RestoreSetings_E( void );
void SaveSetings_E( void );

#endif /* MACTUATORALGORITHM_MACTUATORALGORITHM_H_ */
