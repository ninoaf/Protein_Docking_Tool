################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pdbparser/atomradius.cpp \
../src/pdbparser/models.cpp \
../src/pdbparser/moleculecolors.cpp \
../src/pdbparser/pdbparser.cpp 

OBJS += \
./src/pdbparser/atomradius.o \
./src/pdbparser/models.o \
./src/pdbparser/moleculecolors.o \
./src/pdbparser/pdbparser.o 

CPP_DEPS += \
./src/pdbparser/atomradius.d \
./src/pdbparser/models.d \
./src/pdbparser/moleculecolors.d \
./src/pdbparser/pdbparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/pdbparser/%.o: ../src/pdbparser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g1 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

