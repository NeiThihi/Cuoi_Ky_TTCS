################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Cuoi_Ki_TTCS
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Cuoi_Ki_TTCS.elf \

MAP_FILES += \
Cuoi_Ki_TTCS.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Cuoi_Ki_TTCS.list \

OBJCOPY_HEX += \
Cuoi_Ki_TTCS.hex \

OBJCOPY_BIN += \
Cuoi_Ki_TTCS.bin \


# All Target
all: main-build

# Main-build Target
main-build: Cuoi_Ki_TTCS.elf secondary-outputs

# Tool invocations
Cuoi_Ki_TTCS.elf Cuoi_Ki_TTCS.map: $(OBJS) $(USER_OBJS) D:\PTITer-102\ki_2_nam_3\De_tai_cuoi_ky_TTCS\Cuoi_Ki_TTCS\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Cuoi_Ki_TTCS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\PTITer-102\ki_2_nam_3\De_tai_cuoi_ky_TTCS\Cuoi_Ki_TTCS\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Cuoi_Ki_TTCS.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Cuoi_Ki_TTCS.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Cuoi_Ki_TTCS.list"
	@echo 'Finished building: $@'
	@echo ' '

Cuoi_Ki_TTCS.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Cuoi_Ki_TTCS.hex"
	@echo 'Finished building: $@'
	@echo ' '

Cuoi_Ki_TTCS.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Cuoi_Ki_TTCS.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Cuoi_Ki_TTCS.bin Cuoi_Ki_TTCS.elf Cuoi_Ki_TTCS.hex Cuoi_Ki_TTCS.list Cuoi_Ki_TTCS.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
