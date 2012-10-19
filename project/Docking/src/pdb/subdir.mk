################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pdb/pdb.cpp 

OBJS += \
./src/pdb/pdb.o 

CPP_DEPS += \
./src/pdb/pdb.d 


# Each subdirectory must supply rules for building sources it contributes
src/pdb/%.o: ../src/pdb/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -L/home/pdt/local/lib -I/home/pdt/local/include/ -lgsl -lgslcblas -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


