/*
 * mKeyboard.h
 *
 *  Created on: 14 lut 2017
 *      Author: Admin
 */

#ifndef MKEYBOARD_MKEYBOARD_H_
#define MKEYBOARD_MKEYBOARD_H_

#define NumOfKey	4	//Liczba klawiszy

#define KEY0_PORT	B
#define KEY0_PIN	6

#define KEY1_PORT	B
#define KEY1_PIN	5

#define KEY2_PORT	B
#define KEY2_PIN	7

#define KEY3_PORT	D
#define KEY3_PIN	3

#define BUTTON0PRESSED	(!(PIN(KEY0_PORT) & (1<<KEY0_PIN)))
#define BUTTON1PRESSED	(!(PIN(KEY1_PORT) & (1<<KEY1_PIN)))
#define BUTTON2PRESSED	(!(PIN(KEY2_PORT) & (1<<KEY2_PIN)))
#define BUTTON3PRESSED	(!(PIN(KEY3_PORT) & (1<<KEY3_PIN)))

typedef enum EButtonPressedState
{
	ButtonPressed_Unpressed,
	ButtonPressed_Short,
	ButtonPressed_Long

}tEButtonPressedState;

typedef enum EButtonState
{
	ButtonState_Unpressed,
	ButtonState_Pressed,
	ButtonState_Hold,
	ButtonState_Released
}tEButtonState;

typedef struct{

	uint16_t iButtonPressedCounter;
	uint8_t iButtonDebounceCycles;
	uint8_t iButtonPressedLongCycles;

}tSButtonRegisters;

void Keyboard_Init( void );

#if NumOfKey > 0
	tEButtonPressedState Keyboard_GetButton0State();
#endif

#if NumOfKey > 1
	tEButtonPressedState Keyboard_GetButton1State();
#endif

#if NumOfKey > 2
	tEButtonPressedState Keyboard_GetButton2State();
#endif

#if NumOfKey > 3
	tEButtonPressedState Keyboard_GetButton3State();
#endif

void Keyboard_Scan( void );

#endif /* MKEYBOARD_MKEYBOARD_H_ */
