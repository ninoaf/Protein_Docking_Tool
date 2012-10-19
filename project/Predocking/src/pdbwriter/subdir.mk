################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pdbwriter/pdbwriter.cpp \
../src/pdbwriter/scoreloader.cpp 

OBJS += \
./src/pdbwriter/pdbwriter.o \
./src/pdbwriter/scoreloader.o 

CPP_DEPS += \
./src/pdbwriter/pdbwriter.d \
./src/pdbwriter/scoreloader.d 


# Each subdirectory must supply rules for building sources it contributes
src/pdbwriter/%.o: ../src/pdbwriter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


