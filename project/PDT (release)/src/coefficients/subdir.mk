################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/coefficients/coefficients.cpp 

OBJS += \
./src/coefficients/coefficients.o 

CPP_DEPS += \
./src/coefficients/coefficients.d 


# Each subdirectory must supply rules for building sources it contributes
src/coefficients/%.o: ../src/coefficients/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g1 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


