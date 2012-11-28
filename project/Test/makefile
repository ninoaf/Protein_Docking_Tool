################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/trigonometriccaching/subdir.mk
-include src/translationmatrix/subdir.mk
-include src/structures/subdir.mk
-include src/scene/subdir.mk
-include src/rotationmatrix/subdir.mk
-include src/protein/subdir.mk
-include src/predocking/subdir.mk
-include src/pdbwriter/subdir.mk
-include src/pdbparser/subdir.mk
-include src/objects/subdir.mk
-include src/msmswrapper/subdir.mk
-include src/math/subdir.mk
-include src/materials/subdir.mk
-include src/gui/subdir.mk
-include src/grid/subdir.mk
-include src/docking/subdir.mk
-include src/configuration/subdir.mk
-include src/command/subdir.mk
-include src/coefficients/subdir.mk
-include src/basefunctions/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PDT_v3

# Tool invocations
PDT_v3: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "PDT_v3" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) PDT_v3
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
