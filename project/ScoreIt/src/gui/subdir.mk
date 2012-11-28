################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gui/glwindow.cpp \
../src/gui/guicallbacksdisplay.cpp \
../src/gui/guicallbacksmenu.cpp \
../src/gui/guicallbacksnodes.cpp \
../src/gui/guicallbacksoptions.cpp \
../src/gui/guicallbackspdt.cpp \
../src/gui/guicallbacksvariables.cpp \
../src/gui/guimenus.cpp \
../src/gui/guitabs.cpp \
../src/gui/textcomandinput.cpp \
../src/gui/vmolgui.cpp 

OBJS += \
./src/gui/glwindow.o \
./src/gui/guicallbacksdisplay.o \
./src/gui/guicallbacksmenu.o \
./src/gui/guicallbacksnodes.o \
./src/gui/guicallbacksoptions.o \
./src/gui/guicallbackspdt.o \
./src/gui/guicallbacksvariables.o \
./src/gui/guimenus.o \
./src/gui/guitabs.o \
./src/gui/textcomandinput.o \
./src/gui/vmolgui.o 

CPP_DEPS += \
./src/gui/glwindow.d \
./src/gui/guicallbacksdisplay.d \
./src/gui/guicallbacksmenu.d \
./src/gui/guicallbacksnodes.d \
./src/gui/guicallbacksoptions.d \
./src/gui/guicallbackspdt.d \
./src/gui/guicallbacksvariables.d \
./src/gui/guimenus.d \
./src/gui/guitabs.d \
./src/gui/textcomandinput.d \
./src/gui/vmolgui.d 


# Each subdirectory must supply rules for building sources it contributes
src/gui/%.o: ../src/gui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


