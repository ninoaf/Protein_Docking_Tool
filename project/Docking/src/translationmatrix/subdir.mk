################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/translationmatrix/translationmatrix.cpp 

OBJS += \
./src/translationmatrix/translationmatrix.o 

CPP_DEPS += \
./src/translationmatrix/translationmatrix.d 


# Each subdirectory must supply rules for building sources it contributes
src/translationmatrix/%.o: ../src/translationmatrix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


