################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/objects/complexmesh.cpp \
../src/objects/load3ds.cpp \
../src/objects/loadDat.cpp \
../src/objects/loadGrid.cpp \
../src/objects/loadMs.cpp \
../src/objects/mesh.cpp 

OBJS += \
./src/objects/complexmesh.o \
./src/objects/load3ds.o \
./src/objects/loadDat.o \
./src/objects/loadGrid.o \
./src/objects/loadMs.o \
./src/objects/mesh.o 

CPP_DEPS += \
./src/objects/complexmesh.d \
./src/objects/load3ds.d \
./src/objects/loadDat.d \
./src/objects/loadGrid.d \
./src/objects/loadMs.d \
./src/objects/mesh.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/%.o: ../src/objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


