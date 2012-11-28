################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/math/evalmath/evaluate.cpp 

C_SRCS += \
../src/math/evalmath/rmallws.c \
../src/math/evalmath/strupr.c 

OBJS += \
./src/math/evalmath/evaluate.o \
./src/math/evalmath/rmallws.o \
./src/math/evalmath/strupr.o 

C_DEPS += \
./src/math/evalmath/rmallws.d \
./src/math/evalmath/strupr.d 

CPP_DEPS += \
./src/math/evalmath/evaluate.d 


# Each subdirectory must supply rules for building sources it contributes
src/math/evalmath/%.o: ../src/math/evalmath/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/math/evalmath/%.o: ../src/math/evalmath/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


