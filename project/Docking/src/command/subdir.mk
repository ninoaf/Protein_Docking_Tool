################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/command/handlecommandchange.cpp \
../src/command/handlecommandcreate.cpp \
../src/command/handlecommandmath.cpp \
../src/command/handlecommandremove.cpp \
../src/command/handlecommandrun.cpp \
../src/command/handlecommands.cpp \
../src/command/handleparameters.cpp \
../src/command/handletemplates.cpp \
../src/command/vmolcommand.cpp 

OBJS += \
./src/command/handlecommandchange.o \
./src/command/handlecommandcreate.o \
./src/command/handlecommandmath.o \
./src/command/handlecommandremove.o \
./src/command/handlecommandrun.o \
./src/command/handlecommands.o \
./src/command/handleparameters.o \
./src/command/handletemplates.o \
./src/command/vmolcommand.o 

CPP_DEPS += \
./src/command/handlecommandchange.d \
./src/command/handlecommandcreate.d \
./src/command/handlecommandmath.d \
./src/command/handlecommandremove.d \
./src/command/handlecommandrun.d \
./src/command/handlecommands.d \
./src/command/handleparameters.d \
./src/command/handletemplates.d \
./src/command/vmolcommand.d 


# Each subdirectory must supply rules for building sources it contributes
src/command/%.o: ../src/command/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


