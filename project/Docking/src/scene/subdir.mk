################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/scene/scene.cpp \
../src/scene/scenenode.cpp 

OBJS += \
./src/scene/scene.o \
./src/scene/scenenode.o 

CPP_DEPS += \
./src/scene/scene.d \
./src/scene/scenenode.d 


# Each subdirectory must supply rules for building sources it contributes
src/scene/%.o: ../src/scene/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -static -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


