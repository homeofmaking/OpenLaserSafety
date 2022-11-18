![OpenLaserSafety Logo](https://user-images.githubusercontent.com/1123412/202749375-a9854286-cd8e-4045-a184-6ae3be98b1f5.svg)

### What is OpenLaserSafety?
OpenLaserSafety is a controller that aims to check various status inputs that are found around (self-built) laser cutters. It then outputs one master "OK" or "NOT OK" signal that can be used to input on most laser controllers (usually through a "door open" or "water protect" input that will stop the laser if not pulled high or low). 

OLS was initially designed to replace the hand soldered first version of a laser safety system used at [Munich Maker Lab](https://github.com/munichmakerlab/). We designed this new version with simplicity and adaptability in mind. It should work 'out of the box' with very little config changes for most self-built laser cutters out there.

### Features

- Supported inputs
  - Water flow sensor (with hall effect sensor, e.g. [this](https://www.aliexpress.com/item/4001114518438.html))
  - Water temperature sensor NTC-Type (e.g. [this](https://www.aliexpress.com/item/1005001521072178.html))
  - Water temperature sensor One-Wire (e.g. [ds1820b or similar](https://www.aliexpress.com/item/1005003111458660.html?))
  - Dip switches/other digital inputs (reed switches, dip switches, ...)
  - External Unlock to support [OpenUnitState Machine Unlocking](https://github.com/homeofmaking/OpenUnitState)
  - Fire suppression systems with separate 12V power supply
  - Pressure sensor for ventilation system status (e.g. [Honeywell HSCMRRD002NDAA5 differential pressure sensor](https://de.farnell.com/en-DE/honeywell/hscmrrd002ndaa5/pressure-sensor-2inch-h2o-analogue/dp/3439034))
- Outputs
  - Master output via dry relays
  - i2c TLC59116 LED-driver support for status LEDs
- On board Wemos D1 mini for user-code
  - Master output and uart from safety uC
  - Runs user software e.g. to log status remotely
- Power management
  - On board converters for 5V and 3.3V
  - Up to 40V input voltage
- Low-cost BOM with all parts available on [jlcpcbs assembly service](https://jlcpcb.com/parts)

### Supporters & Sponsors
Version 1.0 of the PCB has been sponsored by jlcpcb. 

![jlcpcb-300](https://user-images.githubusercontent.com/1123412/202773101-4de48844-dd10-46d2-b594-e24b453b59f9.png)
