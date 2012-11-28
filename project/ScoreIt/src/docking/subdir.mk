################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/docking/docking.cpp \
../src/docking/docking_test.cpp 

OBJS += \
./src/docking/docking.o \
./src/docking/docking_test.o 

CPP_DEPS += \
./src/docking/docking.d \
./src/docking/docking_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/docking/%.o: ../src/docking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


