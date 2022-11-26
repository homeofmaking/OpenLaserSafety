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
- Software allows easy configuration of all inputs and thresholds
- Inputs are using cheap but robust KF301 terminals
- On board Wemos D1 mini for user-code
  - Master output and uart from safety uC
  - Runs user software e.g. to log status remotely
- Power management
  - On board converters for 5V and 3.3V
  - Up to 40V input voltage
- Low-cost BOM with all parts available on [jlcpcbs assembly service](https://jlcpcb.com/parts)

### Pictures

This is what version 1.1 looks like.
![easyeda_HQNySO02Kl](https://user-images.githubusercontent.com/1123412/202814483-bc921fe5-7cd6-4614-846d-bd7e5397b175.png)

### Supporters & Sponsors

Version 1.0 of the PCB has been sponsored by jlcpcb.

![jlcpcb-300](https://user-images.githubusercontent.com/1123412/202773101-4de48844-dd10-46d2-b594-e24b453b59f9.png)

### License

The hardware in this repository is licensed under the [Solderpad Hardware License version 2.1](LICENSE). Software is licensed under the [Apache License 2](LICENSE).
[These licenses are permissive and qualify for the Open Source Hardware definition.](https://www.oshwa.org/definition/) Please refrain from using the OpenLaserSafety brand, including logo and name.

### Credits & Attribution

- Main contributors to hardware design [German Hoeffner](https://github.com/ghoeffner) & [Serge 'q3k' Bazanski](https://github.com/q3k)
- Main contributors to software [Christoph 'Meier' Maser](https://github.com/TheMeier)
- [Original idea by MunichMakerLab LaserSafety contributors.](https://github.com/munichmakerlab/LaserSafety/graphs/contributors)

### Description of PINs

| uC Pin | PCB Header | PCB Name       | FW Name                       | Log Name | Notes                      |
| :----: | ---------- | -------------- | ----------------------------- | :------: | -------------------------- |
|  PA0   | H10        | WA T OUT       | N/A (DMA)                     |   `T2`   |                            |
|  PA1   | U8         | PRESS SENS     | N/A (DMA)                     |  `PRE`   |                            |
|  PA2   | U5         | MISC ANA. IN 2 | N/A (DMA)                     |          |                            |
|  PA3   | U6         | MISC ANA. IN   | N/A (DMA)                     |          |                            |
|  PA4   | H17        | LID2 DI        | DOOR1_GPIO_PIN/TYPE           |   `D1`   | Inverter    #FIXME swapped |
|  PA5   | H12        | FIRE DET       | FIREALARM_GPIO_PIN/TYPE       |  `FIRE`  | Optocoupler                |
|  PA6   | H9         | WA T IN        | N/A (DMA)                     |   `T1`   |                            |
|  PA7   | H13        | MISC3 DI       | SPAREIO1_GPIO_PIN/TYPE        |          |                            |
|  PA8   | U9         | WATERFLOW      | Timer `htim1`                 |  `FLOW`  |                            |
|  PA9   |            | TX             | Uart  `huart1`                |          |                            |
|  PA10  |            | TX             | Uart  `huart1`                |          |                            |
|  PA11  | H18        | VENT DI        | EXHAUST_DIGITAL_GPIO_PIN/TYPE |          | Inverter                   |
|  PA12  | H16        | LID1 DI        | DOOR2_GPIO_PIN/TYPE           |   `D2`   | Inverter    #FIXME swapped |
|  PB0   | U7         | SPARE IO       | SPAREIO1_GPIO_PIN/TYPE        |          |                            |
|  PB1   | H7         | EXT UNL.       | EXTUNLOCK_GPIO_PIN/TYPE       |  `UNL`   |                            |
|  PB12  | H14, H15   | MASTER         | MASTER_OUT_Pin/Port           |          | Dry Relays                 |
|  PB12  | -          | -              |                               |    -     | D5 Pin on Wemos D1         |
|  PB13  | H11        | MISC2 DI       | SPAREIO3_GPIO_PIN/TYPE        |          |                            |
|  PB14  | H8         | MISC1 DI       | SPAREIO4_GPIO_PIN/TYPE        |          |                            |
|  PB2   | U11        | ONEWIRE        | N/A                           |          |                            |
