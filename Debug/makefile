################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./ConfigureRTC.obj" \
"./Crystalfontz128x128_ST7735.obj" \
"./HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" \
"./Lcd.obj" \
"./adc_driver.obj" \
"./aes256.obj" \
"./button.obj" \
"./checkbox.obj" \
"./circle.obj" \
"./comp_e.obj" \
"./context.obj" \
"./cpu.obj" \
"./crc32.obj" \
"./cs.obj" \
"./display.obj" \
"./dma.obj" \
"./flash.obj" \
"./fontcm18i.obj" \
"./fontcm24b.obj" \
"./fontfixed6x8.obj" \
"./fpu.obj" \
"./gpio.obj" \
"./image.obj" \
"./imageButton.obj" \
"./interrupt.obj" \
"./lcdconfig.obj" \
"./line.obj" \
"./main.obj" \
"./mpu.obj" \
"./pcm.obj" \
"./pmap.obj" \
"./pss.obj" \
"./rectangle.obj" \
"./ref_a.obj" \
"./reset.obj" \
"./rtc_c.obj" \
"./spi.obj" \
"./startup_msp432p401r_ccs.obj" \
"./string.obj" \
"./sysctl.obj" \
"./system_msp432p401r.obj" \
"./watch_face_themes.obj" \
"./wdt_a.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
basic_display_v2.out \

EXE_OUTPUTS__QUOTED += \
"basic_display_v2.out" \

BIN_OUTPUTS += \
basic_display_v2.hex \

BIN_OUTPUTS__QUOTED += \
"basic_display_v2.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "basic_display_v2.out"

# Tool invocations
basic_display_v2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"basic_display_v2.map" --heap_size=1024 --stack_size=512 -i"C:/Users/kwat1/Documents/ccsv7/ccs_base/arm/include" -i"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/lib" -i"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="basic_display_v2_linkInfo.xml" --rom_model -o "basic_display_v2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

basic_display_v2.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/Users/kwat1/Documents/ccsv7/tools/compiler/ti-cgt-arm_16.9.4.LTS/bin/armhex" --memwidth=8 --romwidth=8 -o "basic_display_v2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "ConfigureRTC.obj" "Crystalfontz128x128_ST7735.obj" "HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.obj" "Lcd.obj" "adc_driver.obj" "aes256.obj" "button.obj" "checkbox.obj" "circle.obj" "comp_e.obj" "context.obj" "cpu.obj" "crc32.obj" "cs.obj" "display.obj" "dma.obj" "flash.obj" "fontcm18i.obj" "fontcm24b.obj" "fontfixed6x8.obj" "fpu.obj" "gpio.obj" "image.obj" "imageButton.obj" "interrupt.obj" "lcdconfig.obj" "line.obj" "main.obj" "mpu.obj" "pcm.obj" "pmap.obj" "pss.obj" "rectangle.obj" "ref_a.obj" "reset.obj" "rtc_c.obj" "spi.obj" "startup_msp432p401r_ccs.obj" "string.obj" "sysctl.obj" "system_msp432p401r.obj" "watch_face_themes.obj" "wdt_a.obj" 
	-$(RM) "ConfigureRTC.d" "Crystalfontz128x128_ST7735.d" "HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" "Lcd.d" "adc_driver.d" "aes256.d" "button.d" "checkbox.d" "circle.d" "comp_e.d" "context.d" "cpu.d" "crc32.d" "cs.d" "display.d" "dma.d" "flash.d" "fontcm18i.d" "fontcm24b.d" "fontfixed6x8.d" "fpu.d" "gpio.d" "image.d" "imageButton.d" "interrupt.d" "lcdconfig.d" "line.d" "main.d" "mpu.d" "pcm.d" "pmap.d" "pss.d" "rectangle.d" "ref_a.d" "reset.d" "rtc_c.d" "spi.d" "startup_msp432p401r_ccs.d" "string.d" "sysctl.d" "system_msp432p401r.d" "watch_face_themes.d" "wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

