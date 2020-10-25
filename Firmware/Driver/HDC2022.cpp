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

#include <HDC2022.hpp>

/*
 * Example Usage
 *
 *
 * 	#include <HDC2022.hpp>
 *	uint8_t temperature;
 *	uint8_t humidity;
 *	HDC2022_c HDC2022;
 * 	void main()
 * 	{
 * 	 HDC2022.Init(hi2c1,100);
 * 		while(1)
 * 		{
 *			temperature=HDC2022.get_Temperature();
 *			humidityHDC2022.get_Humidity();
 * 		}
 * 	}
 */

/**
 * @brief  General I2C Bus Transmit Function
 * @note   Handler and timeout must be set in the Init() function, otherwise system return error
 * @param  addr_t reg 	: Address Register, must be addr_t type on the header file
 * @param  uint8_t val	: Value of Address Register to send Slave
 * @retval None
 */
void HDC2022_c::I2C_setByte(addr_t reg, uint8_t val)
{
    uint8_t buf_setI2C[2];

    buf_setI2C[0] = reg;
    buf_setI2C[0] = val;
    HAL_I2C_Master_Transmit(&i2c, DeviceID, buf_setI2C, 2, i2c_timeout);

}

/**
 * @brief  General I2C Bus Transmit&Receive Function
 * @note   Handler and timeout must be set in the Init() function, otherwise system return error
 * @param  addr_t reg 	: Address Register, must be addr_t type on the header file
 * @retval uint8_t 	: Value of requested address
 */
uint8_t HDC2022_c::I2C_getByte(addr_t reg)
{

    uint8_t buf_getI2C[2];

    buf_getI2C[0] = reg;
    HAL_I2C_Master_Transmit(&i2c, DeviceID, buf_getI2C, 1, i2c_timeout);
    HAL_I2C_Master_Receive(&i2c, DeviceID, buf_getI2C, 1, i2c_timeout);
    return buf_getI2C[0];

}

/**
 * @brief  Sensor Default values set function
 * @note   Used this function inside of Init Function
 * @param  None
 * @retval None
 */
void HDC2022_c::DeInit()
{

    TEMPERATURE_LOW = 0x00;
    TEMPERATURE_HIGH = 0x00;
    HUMIDITY_LOW = 0x00;
    HUMIDITY_HIGH = 0x00;
    STATUS.val = 0x00;
    TEMPERATURE_MAX = 0x00;
    HUMIDITY_MAX = 0x00;
    INTERRUPT_ENABLE.val = 0x00;
    TEMPERATURE_OFFSET_ADJUSTMENT.val = 0x00;
    HUMIDITY_OFFSET_ADJUSTMENT.val = 0x00;
    TEMPERATURE_THRESHOLD_LOW = 0x01;
    TEMPERATURE_THRESHOLD_HIGH = 0xFF;
    HUMIDITY_THRESHOLD_LOW = 0x00;
    HUMIDITY_THRESHOLD_HIGH = 0xFF;
    DEVICE_CONFIGURATION.val = 0x00;
    MEASUREMENT_CONFIGURATION.val = 0x00;
    MANUFACTURER_ID_LOW = 0x49;
    MANUFACTURER_ID_HIGH = 0x54;
    DEVICE_ID_LOW = 0xD0;
    DEVICE_ID_HIGH = 0X07;
}

/**
 * @brief  Sensor Initialization Function
 * @note   Use in the main function, before the while(1)
 * 		Check Device address is correct
 * @param  I2C_HandleTypeDef I2C_Handler	:	I2C bus handler
 * @param	uint8_t timeout					:	I2C bus timeout
 * @retval None
 */
void HDC2022_c::Init(I2C_HandleTypeDef I2C_Handler, uint8_t timeout)
{

    i2c = I2C_Handler;
    i2c_timeout = timeout;
    DeviceID = DeviceIDLow;
    DeInit();
    set_DeviceConfiguration();
    set_HumidityHIGHThreshold();
    set_HumidityOffset();
    set_HumidityLOWThreshold();
    set_Interrupt();
    set_TemperatureOffset();
    set_TemperatureLOWThreshold();
    set_TemperatureHIGHThreshold();
    set_MeasurementConfiguration();

}

/**
 * @brief  Get Temperature Values
 * @note   read sensor values as byte as and calculate temperature value as a Celsius (°C)
 * @param  None
 * @retval float
 */
float HDC2022_c::get_Temperature()
{

    buffer_8[0] = I2C_getByte(ADDR_TEMPERATURE_LOW);
    buffer_8[1] = I2C_getByte(ADDR_TEMPERATURE_HIGH);


    return ((buffer_8[1] << 8) | (buffer_8[0])) * 1.2589 - 40;
}

/**
 * @brief  Get Humidity Values
 * @note   read sensor values as byte as and calculate humidity value as a  Relative Humidity (RH)
 * @param  None
 * @retval float
 */
float HDC2022_c::get_Humidity()
{

    buffer_8[0] = I2C_getByte(ADDR_HUMIDITY_LOW);
    buffer_8[1] = I2C_getByte(ADDR_HUMIDITY_HIGH);

    return ((buffer_8[1] << 8) | (buffer_8[0])) * 0.763;

}

/**
 * @brief  Get Device Status
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_Status()
{

    STATUS.val = I2C_getByte(ADDR_STATUS);
    return STATUS.val;

}

/**
 * @brief  Get Maximum Temperature
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_MAXTemperature()
{

    return I2C_getByte(ADDR_TEMPERATURE_MAX);

}

/**
 * @brief  Get Maximum Humidity
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_MAXHumidity()
{

    return I2C_getByte(ADDR_HUMIDITY_MAX);

}

/**
 * @brief  Set Interrupt Bits
 * @note	Bitwise assignment example : INTERRUPT_ENABLE.bits.DRDY_ENABLE=1;
 * @param  None
 * @retval None
 */
void HDC2022_c::set_Interrupt()
{
    I2C_setByte(ADDR_INTERRUPT_ENABLE, INTERRUPT_ENABLE.val);
}

/**
 * @brief  Get Interrupt Configuration Register Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_Interrupt()
{

    return I2C_getByte(ADDR_INTERRUPT_ENABLE);

}

/**
 * @brief  Get Temperature Offset Register Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_TemperatureOffset()
{

    return I2C_getByte(ADDR_TEMP_OFFSET_ADJUST);

}

/**
 * @brief  Set Temperature Offset Register Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_TemperatureOffset()
{

    I2C_setByte(ADDR_TEMP_OFFSET_ADJUST, TEMPERATURE_OFFSET_ADJUSTMENT.val);

}

/**
 * @brief  Get Humidity Offset Register Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_HumidityOffset()
{

    return I2C_getByte(ADDR_HUM_OFFSET_ADJUST);

}

/**
 * @brief  Set Humidity Offset Register Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_HumidityOffset()
{

    I2C_setByte(ADDR_HUM_OFFSET_ADJUST, HUMIDITY_OFFSET_ADJUSTMENT.val);

}

/**
 * @brief  Get Temperature Low Threshold Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_TemperatureLOWThreshold()
{

    return I2C_getByte(ADDR_TEMP_THR_L);

}

/**
 * @brief  Set Temperature Low Threshold Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_TemperatureLOWThreshold()
{

    I2C_setByte(ADDR_TEMP_THR_L, TEMPERATURE_THRESHOLD_LOW);

}

/**
 * @brief  Get Temperature High Threshold Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_TemperatureHIGHThreshold()
{

    return I2C_getByte(ADDR_TEMP_THR_H);

}

/**
 * @brief  Set Temperature High Threshold Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_TemperatureHIGHThreshold()
{

    I2C_setByte(ADDR_TEMP_THR_H, TEMPERATURE_THRESHOLD_HIGH);

}

/**
 * @brief  Get Humidity Low Threshold Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_HumidityLOWThreshold()
{

    return I2C_getByte(ADDR_RH_THR_L);

}

/**
 * @brief  Set Humidity Low Threshold Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_HumidityLOWThreshold()
{

    I2C_setByte(ADDR_RH_THR_L, HUMIDITY_THRESHOLD_LOW);

}

/**
 * @brief  Get Humidity High Threshold Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_HumidityHIGHThreshold()
{

    return I2C_getByte(ADDR_RH_THR_H);

}

/**
 * @brief  Set Humidity High Threshold Value
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_HumidityHIGHThreshold()
{

    I2C_setByte(ADDR_RH_THR_H, HUMIDITY_THRESHOLD_HIGH);

}

/**
 * @brief  Set Device Configuration
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_DeviceConfiguration()
{

    I2C_setByte(ADDR_DEVICE_CONFIGURATION, DEVICE_CONFIGURATION.val);

}

/**
 * @brief  Get Device Configuration
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_DeviceConfiguration()
{

    return I2C_getByte(ADDR_DEVICE_CONFIGURATION);

}

/**
 * @brief  Set Measurement Configuration
 * @note	None
 * @param  None
 * @retval None
 */
void HDC2022_c::set_MeasurementConfiguration()
{

    I2C_setByte(ADDR_MEASUREMENT_CONFIGURATION, MEASUREMENT_CONFIGURATION.val);

}

/**
 * @brief  Get Measurement Configuration Register Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_MeasurementConfiguration()
{

    return I2C_getByte(ADDR_MEASUREMENT_CONFIGURATION);

}

/**
 * @brief  Get Manufacturer ID Low Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_ManufacturerIDLOW()
{

    return I2C_getByte(ADDR_MANUFACTURER_ID_LOW);

}

/**
 * @brief  Get Manufacturer ID High Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_ManufacturerIDHIGH()
{

    return I2C_getByte(ADDR_MANUFACTURER_ID_HIGH);

}

/**
 * @brief  Get Device ID Low Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_DeviceIDLOW()
{

    return I2C_getByte(ADDR_DEVICE_ID_LOW);

}

/**
 * @brief  Get Device ID High Value
 * @note	None
 * @param  None
 * @retval uint8_t
 */
uint8_t HDC2022_c::get_DeviceIDHIGH()
{

    return I2C_getByte(ADDR_DEVICE_ID_HIGH);

}

