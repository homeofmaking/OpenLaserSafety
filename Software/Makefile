
all:
	$(MAKE) -C Release $@

clean:
	$(MAKE) -C Release $@

flash: all
	rm -f Release/OpenLaserSafety.bin
	arm-none-eabi-objcopy -O binary Release/OpenLaserSafety.elf Release/OpenLaserSafety.bin
	st-flash --reset write Release/OpenLaserSafety.bin 0x08000000
