# HDC2022-DevelopmentBoard

 ---------------------------------------
 TI HDC2022 Development Board & Firmware


## Hardware


* PCB Design Software : Altium Designer 20.2.5
* Temperature and Humidity Sensor - HDC2022DEPR
* Internal LDO TLV74018PDBVR (1.8V)
* Expansion header for I2C and Power Pins
* PCB size 25x15 mm

<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-001.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-002.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-003.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-004.jpg" width="800">


## Firmware

* IDE : STM32CubeIDE 1.4.0
* MCU : STM32L476RG-Nucleo
* Dependency : 
```sh
	#include <stdint.h>
	#include <stm32l4xx_hal.h>
```
* Usage Example: 
```sh
 	#include <HDC2022.hpp>
	uint8_t temperature;
	uint8_t humidity;
	HDC2022_c HDC2022;
 	void main()
 	{
 	 HDC2022.Init(hi2c1,100);
 		while(1)
 		{
			temperature=HDC2022.get_Temperature();
			humidity=HDC2022.get_Humidity();
 		}
 	}
```
# License
GNU GPLv3 (both hardware and experimental software)

