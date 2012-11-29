################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/rmsd/rmsd_test.cpp 

OBJS += \
./src/rmsd/rmsd_test.o 

CPP_DEPS += \
./src/rmsd/rmsd_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/rmsd/%.o: ../src/rmsd/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


