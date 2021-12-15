/*
 * mScreenEngine.c
 *
 *  Created on: 12 mar 2017
 *      Author: Admin
 */

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>

#include "mLcdScreenEngineV2.h"
#include "../LCD/lcd44780.h"
#include "../mGlobal/mglobal.h"

char MainBufferXY[ScreenColumns][ScreenLines];						//sumowany bufor g³ówny
//char ScreenBufferLYX[ScreenLayers][ScreenLines][ScreenColumns];	//bufory warstw
uint8_t ScrBufferChanged = idle;

#if Use_ScreenRefresh == 1
void ScreenRefresh( void ){
//	static uint8_t LCD_ReinitTimer = 10;

	if( ScrBufferChanged == changed ){
		ScrBufferChanged = idle;

//		if( LCD_ReinitTimer ){
//			LCD_ReinitTimer--;
//		}else{
//			LCD_ReinitTimer = 10;
//			lcd_init();
//		}

		SendMainBufToLcd();
	}
}
#endif

#if Use_PrepMainBuf == 1
void PrepMainBuf( void ){

}
#endif

#if Use_SendMainBufToLcd == 1
void SendMainBufToLcd( void ){
//***********************************************************************************

//	czas wykonania funkcji przy zegarze 8MHz dla LCD 2x16 -> ok 2ms ( ATmega32L )

//***********************************************************************************

	uint8_t i,j;
	char buf[ScreenColumns];

	lcd_cls();

	for( j=0; j<ScreenLines ; j++ ){

		for( i=0; i<ScreenColumns ; i++ ){
			buf[i] = MainBufferXY[i][j];

		}//end for in

		lcd_locate( j,0 );
		lcd_str( buf );
	}//end for out

}
#endif

#if Use_ScrMainBufClr == 1
void ScrMainBufClr( void ){


	for( uint8_t i = 0; i<ScreenColumns ;i++ ){

		for( uint8_t j = 0; j<ScreenLines ;j++ ){
			MainBufferXY[i][j] = ' ';
		}//end for in

	}//end for out

	ScrBufferChanged = changed;

}
#endif

#if Use_ScrMainBufLnClr == 1
void ScrMainBufLnClr( uint8_t line ){

		for( uint8_t i = 0; i<ScreenColumns ;i++ ){
			MainBufferXY[i][line] = ' ';
		}//end for in
		ScrBufferChanged = changed;
}
#endif

#if Use_ScrRoR == 1
void ScrRoR( uint8_t line ){

	char buf;

		buf = MainBufferXY[ScreenColumns-1][line];

		for( uint8_t i=0;i<(ScreenColumns-1);i++ ){

			MainBufferXY[ScreenColumns-1-i][line] = MainBufferXY[ScreenColumns-2-i][line];

	}
		MainBufferXY[0][line] = buf;
		ScrBufferChanged = changed;
}
#endif

#if Use_ScrRoL == 1
void ScrRoL( uint8_t line ){

	char buf;

		buf = MainBufferXY[0][line];

		for( uint8_t i=0;i<(ScreenColumns-1);i++ ){

			MainBufferXY[i][line] = MainBufferXY[i+1][line];

	}
		MainBufferXY[ScreenColumns-1][line] = buf;
		ScrBufferChanged = changed;
}
#endif

#if Use_ScrVarLoc == 1
void ScrVarLoc(uint16_t * var, uint8_t x, uint8_t y, uint8_t length){

	char buf[8];
	uint8_t i = length-1;

	if( (x+i)<=15 ) {
		while( i<length ){ MainBufferXY[x+i][y] = ' '; i--;  }
	}

	itoa(*var,buf,10);

	i = 0;
	while( buf[i] ){ MainBufferXY[x+i][y] = buf[i]; i++; }
	ScrBufferChanged = changed;
}
#endif

#if Use_ScrStaticTextLoc == 1
void ScrStaticTextLoc( char * SText, uint8_t x , uint8_t y ){

	register char znak;
	uint8_t i = 0;
	while( (znak = *(SText++)) ){ MainBufferXY[x+i][y] = znak; i++;}
	ScrBufferChanged = changed;
}
#endif
#if Use_ScrStaticTextLoc_P == 1

void ScrStaticTextLoc_P( const char * SText, uint8_t x , uint8_t y ){

	register char znak;
	uint8_t i = 0;
	while( (znak = pgm_read_byte(SText++)) ){ MainBufferXY[x+i][y] = znak; i++;}
	ScrBufferChanged = changed;
}

#endif

