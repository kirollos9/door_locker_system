################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../main22.c \
../motor.c \
../pwm.c \
../timer0.c \
../twi.c \
../uart.c 

OBJS += \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./main22.o \
./motor.o \
./pwm.o \
./timer0.o \
./twi.o \
./uart.o 

C_DEPS += \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./main22.d \
./motor.d \
./pwm.d \
./timer0.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


