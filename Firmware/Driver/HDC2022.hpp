/*
 @
 @   Date               :        25.10.2020 / Sunday
 @
 @   Contact            :        M.Rasit KIYAK                    mrstkyk@gmail.com
 @
 @   License            :        GNU AFFERO GENERAL PUBLIC LICENSE v3
 @
 @   Description        :        This Library for HDC2022 Temperature & Humidity Sensor from Texas Instruments
 @
 @   Version            :        1.0.0
 */

#ifndef _HDC2022_HPP_
#define _HDC2022_HPP_

#include <stdint.h>
#include <stm32l4xx_hal.h>


class HDC2022_c {

public:
  
  void      Init (I2C_HandleTypeDef I2C_Handler, uint8_t timeout);
  void      DeInit ();

  float     get_Temperature();
  float     get_Humidity();
  uint8_t   get_Status();

  uint8_t   get_MAXTemperature();
  uint8_t   get_MAXHumidity();

  void      set_Interrupt();
  uint8_t   get_Interrupt();

  uint8_t   get_TemperatureOffset();
  void      set_TemperatureOffset();

  uint8_t   get_HumidityOffset();
  void      set_HumidityOffset();

  uint8_t   get_TemperatureLOWThreshold();
  void      set_TemperatureLOWThreshold();

  uint8_t   get_TemperatureHIGHThreshold();
  void      set_TemperatureHIGHThreshold();

  uint8_t   get_HumidityLOWThreshold();
  void      set_HumidityLOWThreshold();

  uint8_t   get_HumidityHIGHThreshold();
  void      set_HumidityHIGHThreshold();

  void      set_DeviceConfiguration();
  uint8_t   get_DeviceConfiguration();

  void      set_MeasurementConfiguration();
  uint8_t   get_MeasurementConfiguration();

  uint8_t   get_ManufacturerIDLOW();
  uint8_t   get_ManufacturerIDHIGH();

  uint8_t   get_DeviceIDLOW();
  uint8_t   get_DeviceIDHIGH();



 union
{
       uint8_t val;
       union{
                 struct
                {
                  uint8_t :3; //Reserved
                  uint8_t HL_ENABLE:1; //Humidity threshold LOW Interrupt enable
                  uint8_t HH_ENABLE:1; //Humidity threshold HIGH Interrupt enable
                  uint8_t TL_ENABLE:1; //Temperature threshold LOW Interrupt enable
                  uint8_t TH_ENABLE:1; //Temperature threshold HIGH Interrupt enable
                  uint8_t DRDY_ENABLE:1; //DataReady Interrupt enable
                };
       }bits;
}INTERRUPT_ENABLE; /* The Interrupt Enable register enables or disables interrupt asserstion on the DRDY/INT pin  */

union
{
      uint8_t val;
      union{
                struct
               {
                 uint8_t bit0:1; // +0.16°C
                 uint8_t bit1:1; // +0.32°C
                 uint8_t bit2:1; // +0.64°C
                 uint8_t bit3:1; // +1.29°C
                 uint8_t bit4:1; // +2.58°C
                 uint8_t bit5:1; // +5.16°C
                 uint8_t bit6:1; // +10.31°C
                 uint8_t bit7:1; // –20.63°C
               };
      }bits;
}TEMPERATURE_OFFSET_ADJUSTMENT; /*  Temperature offset adjustment value. The value is added to the converted temperature data.  */

union
{
      uint8_t val;
      union{
                struct
               {
                 uint8_t bit0:1;  /*  +0.2%RH   */
                 uint8_t bit1:1;  /*  +0.4%RH   */
                 uint8_t bit2:1;  /*  +0.8%RH   */
                 uint8_t bit3:1;  /*  +1.6%RH   */
                 uint8_t bit4:1;  /*  +3.1%RH   */
                 uint8_t bit5:1;  /*  +6.3%RH   */
                 uint8_t bit6:1;  /*  +12.5%RH  */
                 uint8_t bit7:1;  /*  –25%RH    */
               };
      }bits;
}HUMIDITY_OFFSET_ADJUSTMENT; /* Humidity offset adjustment value. The value is added to the converted humidity data.  */

uint8_t TEMPERATURE_THRESHOLD_LOW;  /*  Temperature threshold LOW value   */
uint8_t TEMPERATURE_THRESHOLD_HIGH; /*  Temperature threshold HIGH value  */

uint8_t HUMIDITY_THRESHOLD_LOW;     /*  Humidity threshold LOW value      */
uint8_t HUMIDITY_THRESHOLD_HIGH;    /*  Humidity threshold HIGH value     */

 union
{
       uint8_t val;
       union{
                 struct
                {
                  uint8_t INT_MODE:1;     /*  Interrupt mode                : 0 = Clear-on-read mode, 1 = Comparator mode       */
                  uint8_t INT_POL:1;      /*  Interrupt polarity            : 0 = Active Low, 1 = Active High                   */
                  uint8_t DRDY__INT_EN:1; /*  DRDY/INT_EN pin configuration : 0 = High Z, 1 = Enable                            */
                  uint8_t HEAT_EN:1;      /*  0 = Heater off, 1 = Heater on                                                     */
                  uint8_t CC:3;           /*  Configure the measurement mode to one-shot or continuous conversion               */
                  uint8_t SOFT_RES:1;     /*  0 = Normal Operation, 1 = Trigger a Soft Reset. This bit self-clears after RESET. */
                };
       }bits;
}DEVICE_CONFIGURATION;

 union
{
       uint8_t val;
       union{
                 struct
                {
                  uint8_t MEAS_TRIG:1;  /*  Measurement trigger         - 0: No action, 1: Start measurement                                */
                  uint8_t MEAS_CONF:2;  /*  Measurement configuration   - 00: Humidity + Temperature, 01: Temperature only, 10: NA, 11: NA  */
                  uint8_t :1;           /*  Reserved                                                                                        */
                  uint8_t HACC:2;       /*  Humidity accuracy option    - 00 : 14 bit, 01 : 11 bit, 10 : 9 bit, 11 : NA                     */
                  uint8_t TACC:2;       /*  Temperature accuracy option - 00 : 14 bit, 01 : 11 bit, 10 : 9 bit, 11 : NA                     */
                };
       }bits;
}MEASUREMENT_CONFIGURATION;

private:

I2C_HandleTypeDef i2c;
uint8_t i2c_timeout = 100;
uint8_t DeviceID;
uint8_t DeviceIDHigh = 0x41<<1;
uint8_t DeviceIDLow = 0x40<<1;
uint8_t buffer_8[5];

uint8_t TEMPERATURE_LOW;  /* Temperature data- lower byte  */
uint8_t TEMPERATURE_HIGH; /* Temperature data- higher byte */

uint8_t HUMIDITY_LOW;     /*  Humidity data- lower byte    */
uint8_t HUMIDITY_HIGH;    /*  Humidity data- higher byte   */


 union
{
       uint8_t val;
       union{
                 struct
                {
                  uint8_t :3;            /*  Reserved                                   */
                  uint8_t HL_STATUS:1;   /* Humidity threshold LOW Interrupt status     */
                  uint8_t HH_STATUS:1;   /* Humidity threshold HIGH Interrupt status    */
                  uint8_t TL_STATUS:1;   /* Temperature threshold LOW Interrupt status  */
                  uint8_t TH_STATUS:1;   /* Temperature threshold HIGH Interrupt status */
                  uint8_t DRDY_STATUS:1; /* DataReady bit status                        */
                };
       }bits;
}STATUS;

uint8_t TEMPERATURE_MAX; /* Maximum temperature measurement data (one-shot mode only) */
uint8_t HUMIDITY_MAX;    /* Maximum humidity measurement data (one-shot mode only)    */



uint8_t MANUFACTURER_ID_LOW;  /*  The Manufacturer ID Low and Manufacturer ID High registers contain a factory-programmable identification value that identifies this device as being manufactured by Texas Instruments.  */
uint8_t MANUFACTURER_ID_HIGH; /*  The Manufacturer ID Low and Manufacturer ID High registers contain a factory-programmable identification value that identifies this device as being manufactured by Texas Instruments.  */

uint8_t DEVICE_ID_LOW;        /*  The Device ID Low and Device ID High registers contain a factory-programmable identification value that identifies this device as a HDC2022.  */
uint8_t DEVICE_ID_HIGH;       /*  The Device ID Low and Device ID High registers contain a factory-programmable identification value that identifies this device as a HDC2022.  */


   typedef enum
  {
    ADDR_TEMPERATURE_LOW = 0x00,      /*  R    Temperature data [7:0]                                   */
    ADDR_TEMPERATURE_HIGH,            /*  R    Temperature data [15:8]                                  */
    ADDR_HUMIDITY_LOW,                /*  R    Humidity data [7:0]                                      */
    ADDR_HUMIDITY_HIGH,               /*  R    Humidity data [15:8]                                     */
    ADDR_STATUS,                      /*  R    DataReady and threshold status                           */
    ADDR_TEMPERATURE_MAX,             /*  R    Maximum measured temperature (one-shot mode only)        */
    ADDR_HUMIDITY_MAX,                /*  R    Maximum measured humidity (one-shot mode only)           */
    ADDR_INTERRUPT_ENABLE,            /*  R/W  Interrupt enable                                         */
    ADDR_TEMP_OFFSET_ADJUST,          /*  R/W  Temperature offset adjustment                            */
    ADDR_HUM_OFFSET_ADJUST,           /*  R/W  Humidity offset adjustment                               */
    ADDR_TEMP_THR_L,                  /*  R/W  Temperature threshold low                                */
    ADDR_TEMP_THR_H,                  /*  R/W  Temperature threshold high                               */
    ADDR_RH_THR_L,                    /*  R/W  Humidity threshold low                                   */
    ADDR_RH_THR_H,                    /*  R/W  Humidity threshold high                                  */
    ADDR_DEVICE_CONFIGURATION,        /*  R/W  Soft reset and interrupt reporting configuration         */
    ADDR_MEASUREMENT_CONFIGURATION,   /*  R/W  Device measurement configuration                         */
    ADDR_MANUFACTURER_ID_LOW = 0xFC,  /*  R    Manufacturer ID lower-byte                               */
    ADDR_MANUFACTURER_ID_HIGH,        /*  R    Manufacturer ID higher-byte                              */
    ADDR_DEVICE_ID_LOW,               /*  R    Device ID lower-byte                                     */
    ADDR_DEVICE_ID_HIGH,              /*  R    Device ID higher-byte                                    */
  }addr_t;

  void    I2C_setByte(addr_t reg, uint8_t val);
  uint8_t I2C_getByte(addr_t reg);


};
#endif
