################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/rotationmatrix/rotationmatrix.cpp 

OBJS += \
./src/rotationmatrix/rotationmatrix.o 

CPP_DEPS += \
./src/rotationmatrix/rotationmatrix.d 


# Each subdirectory must supply rules for building sources it contributes
src/rotationmatrix/%.o: ../src/rotationmatrix/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g1 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


