/*
 * mKeyboard.c
 *
 *  Created on: 14 lut 2017
 *      Author: Admin
 */

#include <avr/io.h>
#include "mKeyboard.h"
#include "../mGlobal/mglobal.h"

volatile uint16_t iButtonPressedCounter = 0;
volatile uint8_t iButtonDebounceCycles = 2;
volatile uint8_t iButtonPressedLongCycles = 100;

volatile tSButtonRegisters ButtonRegisters[NumOfKey];

volatile tEButtonState buttonState[NumOfKey];// = ButtonState_Unpressed;
volatile tEButtonPressedState buttonPressed[NumOfKey];// = ButtonPressed_Unpressed;

void Keyboard_Init( void ){

#if NumOfKey > 0

	ButtonRegisters[0].iButtonPressedCounter = 0;
	ButtonRegisters[0].iButtonDebounceCycles = 2;
	ButtonRegisters[0].iButtonPressedLongCycles = 100;

	DDR( KEY0_PORT ) &= ~( 1<<KEY0_PIN );
	PORT( KEY0_PORT ) |= ( 1<<KEY0_PIN );

#endif

#if NumOfKey > 1

	ButtonRegisters[1].iButtonPressedCounter = 0;
	ButtonRegisters[1].iButtonDebounceCycles = 2;
	ButtonRegisters[1].iButtonPressedLongCycles = 100;

	DDR( KEY1_PORT ) &= ~( 1<<KEY1_PIN );
	PORT( KEY1_PORT ) |= ( 1<<KEY1_PIN );

#endif

#if NumOfKey > 2

	ButtonRegisters[2].iButtonPressedCounter = 0;
	ButtonRegisters[2].iButtonDebounceCycles = 2;
	ButtonRegisters[2].iButtonPressedLongCycles = 100;

	DDR( KEY2_PORT ) &= ~( 1<<KEY2_PIN );
	PORT( KEY2_PORT ) |= ( 1<<KEY2_PIN );

#endif

#if NumOfKey > 3

	ButtonRegisters[3].iButtonPressedCounter = 0;
	ButtonRegisters[3].iButtonDebounceCycles = 2;
	ButtonRegisters[3].iButtonPressedLongCycles = 100;

	DDR( KEY3_PORT ) &= ~( 1<<KEY3_PIN );
	PORT( KEY3_PORT ) |= ( 1<<KEY3_PIN );

#endif

}

#if NumOfKey > 0

tEButtonPressedState Keyboard_GetButton0State()
{
	tEButtonPressedState retVal = buttonPressed[0];
	buttonPressed[0] = ButtonPressed_Unpressed;
	return retVal;
}

#endif

#if NumOfKey > 1

tEButtonPressedState Keyboard_GetButton1State()
{
	tEButtonPressedState retVal = buttonPressed[1];
	buttonPressed[1] = ButtonPressed_Unpressed;
	return retVal;
}

#endif

#if NumOfKey > 2

tEButtonPressedState Keyboard_GetButton2State()
{
	tEButtonPressedState retVal = buttonPressed[2];
	buttonPressed[2] = ButtonPressed_Unpressed;
	return retVal;
}

#endif

#if NumOfKey > 3

tEButtonPressedState Keyboard_GetButton3State()
{
	tEButtonPressedState retVal = buttonPressed[3];
	buttonPressed[3] = ButtonPressed_Unpressed;
	return retVal;
}

#endif

void Keyboard_Scan( void ){

	uint8_t KeysStatus[NumOfKey];

	#if NumOfKey > 0
	KeysStatus[0] = BUTTON0PRESSED;
	#endif

	#if NumOfKey > 1
	KeysStatus[1] = BUTTON1PRESSED;
	#endif

	#if NumOfKey > 2
	KeysStatus[2] = BUTTON2PRESSED;
	#endif

	#if NumOfKey > 3
	KeysStatus[3] = BUTTON3PRESSED;
	#endif

	for(uint8_t i = 0; i < NumOfKey; i++){//begin for

	switch(buttonState[i])
	{//begin switch
		case ButtonState_Unpressed:
			if (KeysStatus[i]) buttonState[i] = ButtonState_Pressed;
			break;

		case ButtonState_Pressed:
			buttonState[i] = ButtonState_Hold;
			break;

		case ButtonState_Hold:
			ButtonRegisters[i].iButtonPressedCounter ++;
			if (ButtonRegisters[i].iButtonPressedCounter >= ButtonRegisters[i].iButtonDebounceCycles && (!KeysStatus[i]))
			{
				buttonState[i] = ButtonState_Released;
				if (buttonPressed[i] != ButtonPressed_Long) buttonPressed[i] = ButtonPressed_Short;
			}
			if (ButtonRegisters[i].iButtonPressedCounter >= ButtonRegisters[i].iButtonPressedLongCycles)
			{
				buttonPressed[i] = ButtonPressed_Long;
			}
			break;

		case ButtonState_Released:
			ButtonRegisters[i].iButtonPressedCounter = 0;
			buttonState[i] = ButtonState_Unpressed;
			break;
	}//end switch

	}//end for

}

void Alt_Keyboard_Scan( void ){



}

