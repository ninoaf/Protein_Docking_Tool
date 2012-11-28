################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/predocking/predocking.cpp \
../src/predocking/predocking_test.cpp 

OBJS += \
./src/predocking/predocking.o \
./src/predocking/predocking_test.o 

CPP_DEPS += \
./src/predocking/predocking.d \
./src/predocking/predocking_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/predocking/%.o: ../src/predocking/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


