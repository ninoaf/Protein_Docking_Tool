################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/basefunctions/basefunctions.cpp 

OBJS += \
./src/basefunctions/basefunctions.o 

CPP_DEPS += \
./src/basefunctions/basefunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/basefunctions/%.o: ../src/basefunctions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g1 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


