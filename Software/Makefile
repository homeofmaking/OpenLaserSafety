export PATH := $(PATH):/opt/st/stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.10.3-2021.10.linux64_1.0.0.202111181127/tools/bin:/opt/st/stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.make.linux64_2.0.100.202202231230/tools/bin


all:
	$(MAKE) -C Debug $@

clean:
	$(MAKE) -C Debug $@

flash: all
	rm Debug/OpenLaserSafety.bin
	arm-none-eabi-objcopy -O binary Debug/OpenLaserSafety.elf Debug/OpenLaserSafety.bin
	st-flash --reset write Debug/OpenLaserSafety.bin 0x08000000
