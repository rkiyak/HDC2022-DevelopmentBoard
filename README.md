![alt text](https://socialify.git.ci/T-RK/HDC2022-DevelopmentBoard/image?description=1&font=Bitter&forks=1&issues=1&language=1&pattern=Circuit%20Board&pulls=1&stargazers=1&theme=Dark)

# HDC2022-DevelopmentBoard
 `TI HDC2022 Development Board & Firmware`
 
[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://github.com/T-RK/HDC2022-DevelopmentBoard/tree/main/Firmware/Driver)



## Hardware

* Temperature and Humidity Sensor - HDC2022DEPR
* External LDO - TLV74018PDBVR (1.8V)
* Level Translator MOSFETs
* Expansion header for I2C and Power Pins
* PCB dimension 25x15 mm

<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-001.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-002.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-003.jpg" width="800">
<img src="Hardware/HDC2022 PCB Design/Project Outputs for HDC2022/HDC2022-page-004.jpg" width="800">



## Firmware

* IDE : STM32CubeIDE
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

