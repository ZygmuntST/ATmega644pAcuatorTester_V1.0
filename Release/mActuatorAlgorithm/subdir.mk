################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mActuatorAlgorithm/mActuatorAlgorithm.c 

OBJS += \
./mActuatorAlgorithm/mActuatorAlgorithm.o 

C_DEPS += \
./mActuatorAlgorithm/mActuatorAlgorithm.d 


# Each subdirectory must supply rules for building sources it contributes
mActuatorAlgorithm/%.o: ../mActuatorAlgorithm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


