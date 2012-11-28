################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/msmswrapper/msmswrapper.cpp 

OBJS += \
./src/msmswrapper/msmswrapper.o 

CPP_DEPS += \
./src/msmswrapper/msmswrapper.d 


# Each subdirectory must supply rules for building sources it contributes
src/msmswrapper/%.o: ../src/msmswrapper/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


