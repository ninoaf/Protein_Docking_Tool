################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/structures/structures.cpp \
../src/structures/vmolstructures.cpp 

OBJS += \
./src/structures/structures.o \
./src/structures/vmolstructures.o 

CPP_DEPS += \
./src/structures/structures.d \
./src/structures/vmolstructures.d 


# Each subdirectory must supply rules for building sources it contributes
src/structures/%.o: ../src/structures/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


