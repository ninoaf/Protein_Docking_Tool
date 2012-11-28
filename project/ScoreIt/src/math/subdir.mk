################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/math/angles.cpp \
../src/math/axisalignment.cpp \
../src/math/laguerre.cpp \
../src/math/legendre.cpp \
../src/math/wigner.cpp 

OBJS += \
./src/math/angles.o \
./src/math/axisalignment.o \
./src/math/laguerre.o \
./src/math/legendre.o \
./src/math/wigner.o 

CPP_DEPS += \
./src/math/angles.d \
./src/math/axisalignment.d \
./src/math/laguerre.d \
./src/math/legendre.d \
./src/math/wigner.d 


# Each subdirectory must supply rules for building sources it contributes
src/math/%.o: ../src/math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


