/*
 * mScreenEngine.h
 *
 *  Created on: 12 mar 2017
 *
 *  *** Biblioteka silnika tekstowego dla wy�wietlaczy znakowych. ***
 *
 *  Wersja 		: 1.0
 *  Pliki		: mLcdScreenEngine.h , mLcdScreenEngine.c
 *  Data		: marzec 2017
 * 	Autor		: Pingwin
 * 	e-mail		: www.erommel555@gmail.com
 *
 *  ************************************************
 *  UWAGI:
 *
 *  Biblioteka zosta�a napisana z my�l� o wykorzystaniu na dowolnym mikrokontrolerze, w zwi�zku z tym
 *  funkcje obs�ugi wy�wietlacza nale�y oprogramowa� we w�asnym zakresie.
 *  Do pracy z wy�wietlaczami zgodnymi z HD44780 na mikrokontrolerach rodziny AVR
 *  wykorzystano bibliotek� autorstwa Miros�awa Kardasia.
 *
 *  Pliki 			: lcd44780.c , lcd44780.h
 *  Mikrokontrolery : Atmel AVR
 *  Kompilator 		: avr-gcc
 *  �r�d�o 			: http://www.atnel.pl
 *  Data 			: marzec 2010
 *
 * ************************************************
 *
 */

#ifndef MLCDSCREENENGINE_MLCDSCREENENGINE_H_
#define MLCDSCREENENGINE_MLCDSCREENENGINE_H_

uint8_t ScrBufferChanged;

#define ScreenLayers	1			//obs�uga warstw nieoprogramowana
#define ScreenLines		2
#define ScreenColumns	16

#define Use_ScreenRefresh		1
#define Use_PrepMainBuf			0
#define Use_SendMainBufToLcd	1
#define Use_ScrMainBufClr		1
#define Use_ScrMainBufLnClr		1
#define Use_ScrRoR				1
#define Use_ScrRoL				1
#define Use_ScrVarLoc			1
#define Use_ScrStaticTextLoc	1
#define Use_ScrStaticTextLoc_P	1
#define Use_ScrBufferCheck		1

#if Use_ScreenRefresh == 1

void ScreenRefresh( void );
/* Wysy�a g��wny bufor je�li nast�pi�a w nim jaka� zmiana */
#endif

#if Use_PrepMainBuf == 1
void PrepMainBuf( void );
/* Przygotowuje g��wny bufor */
#endif

#if Use_SendMainBufToLcd == 1
void SendMainBufToLcd( void );
/* Wysy�a g��wny bufor na wy�wietlacz */
#endif

#if Use_ScrMainBufClr == 1
void ScrMainBufClr( void );
/* Czy�ci ca�y g��wny bufor */
#endif

#if Use_ScrMainBufLnClr == 1
void ScrMainBufLnClr( uint8_t line );
/* Czy�ci jedn� lini� g��wnego bufora */
#endif

#if Use_ScrRoR == 1
void ScrRoR( uint8_t line );
/* Roluje lini� bufora w prawo */
#endif

#if Use_ScrRoL == 1
void ScrRoL( uint8_t line );
/* Roluje lini� bufora w lewo */
#endif

#if Use_ScrVarLoc == 1
void ScrVarLoc( uint16_t * var, uint8_t x, uint8_t y, uint8_t length);
/* Umieszcza zmienn� ca�kowit� w wybranym punkcie bufora */
#endif

#if Use_ScrStaticTextLoc == 1
void ScrStaticTextLoc( char * SText, uint8_t x , uint8_t y );
/* Umieszcza tekst statyczny w wybranym punkcie bufora */
#endif

#if Use_ScrStaticTextLoc_P == 1

void ScrStaticTextLoc_P( const char * SText, uint8_t x , uint8_t y );
/* Umieszcza tekst statyczny z pami�ci programu w wybranym punkcie bufora */
#endif


#endif /* MLCDSCREENENGINE_MLCDSCREENENGINE_H_ */
