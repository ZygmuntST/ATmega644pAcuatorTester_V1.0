################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mLcdScreenEngineV2/mLcdScreenEngineV2.c 

OBJS += \
./mLcdScreenEngineV2/mLcdScreenEngineV2.o 

C_DEPS += \
./mLcdScreenEngineV2/mLcdScreenEngineV2.d 


# Each subdirectory must supply rules for building sources it contributes
mLcdScreenEngineV2/%.o: ../mLcdScreenEngineV2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


