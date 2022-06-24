/*
*****************************************************************************
@file         Deneyap_SicaklikNemBasincOlcer.cpp
@mainpage     Deneyap Temperature&Humidity, Barometer Sensor SHT4X Arduino 
              library source file
@maintainer   RFtek Electronics <techsupport@rftek.com.tr>
@version      v1.0.0
@date         June 24, 2022
@brief        Includes functions to control Deneyap Temperature&Humidity, 
              Barometer Sensor SHT4X Arduino library

Library includes:
--> Configuration functions
--> Data manipulation functions
--> I2C communication functions
*****************************************************************************
*/

#include "Deneyap_SicaklikNemBasincOlcer.h"

SHT4x::SHT4x() {}

/**
  * @brief  I2C initialization and read check  
  * @param  adress: Device adress 
  * @retval None
**/
bool SHT4x::begin(uint8_t address, TwoWire &wirePort) {
   
  Wire.begin(); 
  Wire.beginTransmission(address);
  if(!Wire.endTransmission())
     return true;
  return false;     
}

/**
 * @brief  Check a CRC checksum against a given value
 * @param  2 byte data to check, 1 byte CRC to compare against
 * @retval  true if CRC matched, false otherwise
 **/
bool SHT4x::checkCRC(uint16_t data, unsigned char crc)
{
    unsigned char data_uint8[2] = {(unsigned char)(data & 0xFF), (unsigned char)(data >> 8)};
    unsigned char comp_crc = 0xFF;
    unsigned char poly = 0x31;

    unsigned char i = 2;
    while (i--)
    {
        comp_crc ^= data_uint8[i];
        unsigned char j = 8;
        do
        {
            if (comp_crc & 0x80)
                comp_crc = (comp_crc << 1) ^ poly;
            else
                comp_crc <<= 1;
        } while (--j);
    }

    return (crc ^ comp_crc) == 0;
}

/**
 * @brief  A command to the sensor
 * @param  Command to send
 * @retval  A status code telling whether the command was acknowledged
 **/
SHT4X_Status_TypeDef SHT4x::sendCommand(SHT4X_Commands_TypeDef cmd)
{
    this->abort();
    this->_i2c->beginTransmission((unsigned char)this->_address);
    this->_i2c->write((unsigned char)cmd);

    if (this->_i2c->endTransmission())
        return SHT4X_STATUS_ERROR;

    return SHT4X_STATUS_OK;
}

/**
 * @brief  Send a measurement command to the sensor
 * @param  Command to send
 * @retval  A status code telling whether the command was acknowledged
 **/
SHT4X_Status_TypeDef SHT4x::sendCommand(SHT4X_MeasurementModes_TypeDef cmd)
{
    return sendCommand((SHT4X_Commands_TypeDef)cmd);
}

/**
 * @brief  Set I2C port instance
 * @param  wirePort: I2C Wire port instance over which to communicate with the sensor
 * @retval  A status code telling whether a sensor was found on this port
 **/
SHT4X_Status_TypeDef SHT4x::setPort(TwoWire &wirePort)
{
    // we store the I2C port reference here instead of in constructor as it allows
    // defining objects globally
    this->_i2c = &wirePort;
    this->_i2c->begin();
    return this->checkSerial();
}

/**
 * @brief  Set chip type
 * @param  type: sensor type (see SHT4X_ChipTypes_TypeDef definition for details)
 * @retval  None
 **/
void SHT4x::setChipType(SHT4X_ChipTypes_TypeDef type)
{
    switch (type)
    {
    case SHT4X_CHIPTYPE_A:
    case SHT4X_CHIPTYPE_B:
        this->_address = type;
        break;
    }
}

/**
 * @brief  Get chip type
 * @param  None
 * @retval  Sensor type (see SHT4X_ChipTypes_TypeDef definition for details)
 **/
SHT4X_ChipTypes_TypeDef SHT4x::getChipType()
{
    return this->_address;
}

/**
 * @brief  Clear I2C buffer
 * @param  None
 * @retval  None
 **/
void SHT4x::_clearBuffer()
{
    // clear I2C buffer
    while (this->_i2c->available())
        this->_i2c->read();
}

/**
 * @brief  Abort an ongoing transaction
 * @param  None
 * @retval  An error status
 **/
SHT4X_Status_TypeDef SHT4x::abort()
{
    this->_clearBuffer();
    this->_busy = false;
    return SHT4X_STATUS_ERROR;
}

/**
 * @brief  Send a soft reset command to the sensor
 * @param  None
 * @retval  A status code telling whether the command was acknowledged
 **/
SHT4X_Status_TypeDef SHT4x::softReset()
{
    return sendCommand(SHT4X_CMD_SFT_RST);
}

/**
 * @brief  Request serial number from the sensor
 * @param  None
 * @retval  A  status code telling whether the command succeeded and serial number passed CRC test
 **/
SHT4X_Status_TypeDef SHT4x::checkSerial()
{
    this->_busy = true;
    this->_clearBuffer();

    if (this->sendCommand(SHT4X_CMD_READ_SERIAL) != SHT4X_STATUS_OK)
        return this->abort();
    delay(10);

    // serial should be 2 16bit words with CRC (=> 6 bytes altogether)
    this->_i2c->requestFrom((unsigned char)this->_address, (unsigned char)6);
    if (this->_i2c->available() != (unsigned char)6)
        return this->abort();
    for (unsigned char i = 0; i < 2; i++)
    {
        unsigned char ser_h = this->_i2c->read();
        unsigned char ser_l = this->_i2c->read();
        unsigned char ser_crc = this->_i2c->read();
        this->serial[i] = (((uint16_t)ser_h << 8) | ((uint16_t)ser_l));
        if (!checkCRC(this->serial[i], ser_crc))
        {
            this->abort();
            return SHT4X_STATUS_CRC_FAIL;
        }
    }

    this->_busy = false;
    return SHT4X_STATUS_OK;
}

/**
 * @brief  Set measurement mode
 * @param  None
 * @retval  mode : the code for the measurement mode (see SHT4X_MeasurementModes_TypeDef definition for details)
 **/
void SHT4x::setMode(SHT4X_MeasurementModes_TypeDef mode)
{
    this->_measurement_mode = mode;
}

/**
 * @brief  Get current measurement mode
 * @param  None
 * @retval  The code for the currently set measurement mode (see SHT4X_MeasurementModes_TypeDef definition for details)
 **/
SHT4X_MeasurementModes_TypeDef SHT4x::getMode()
{
    return this->_measurement_mode;
}

/**
 * @brief  Tell the sensor to perform a measurement using the currently set measurement mode
 * @param  None
 * @retval  A status code telling whether the command was acknowledged
 **/
SHT4X_Status_TypeDef SHT4x::measure()
{
    this->TcrcOK = false;
    this->RHcrcOK = false;
    this->_busy = true;

    if (this->sendCommand(this->_measurement_mode) != SHT4X_STATUS_OK)
        return SHT4X_STATUS_ERROR;

    switch (this->_measurement_mode)
    {
    // must wait for a certain amount of time depending on measurement mode;
    // ideally, we would rely on Wire::onReceive callback, but there're a few problems with this one:
    //   1) with Arduino, functional.h is not provided, so one has to set a static function as a callback,
    //      and therefore its not possible to access class members (such as T, RH and serial properties);
    //      I guess it'd be possible to create a static function that takes a class instance as an argument
    //      and returns a function matching onReveive requirements, but I didn't bother to do it yet;
    //   2) with ESP32, there's no implementation of onReceive
    // Therefore, I decided to simply make the function wait for the result until it comes (blocking call!)
    case SHT4X_CMD_MEAS_HI_PREC:
    case SHT4X_CMD_MEAS_MED_PREC:
    case SHT4X_CMD_MEAS_LOW_PREC:
        delay(10);
        break;
    case SHT4X_CMD_HI_HEAT_01S_MEAS:
    case SHT4X_CMD_MED_HEAT_01S_MEAS:
    case SHT4X_CMD_LOW_HEAT_01S_MEAS:
        delay(110);
        break;
    case SHT4X_CMD_HI_HEAT_1S_MEAS:
    case SHT4X_CMD_MED_HEAT_1S_MEAS:
    case SHT4X_CMD_LOW_HEAT_1S_MEAS:
        delay(1010);
        break;
    }
    // data should be 16bit words with CRC (=> 6 bytes altogether)
    this->_i2c->requestFrom((unsigned char)this->_address, (unsigned char)6);
    if (this->_i2c->available() != (unsigned char)6)
        return this->abort();

    unsigned char T_h = this->_i2c->read();
    unsigned char T_l = this->_i2c->read();
    unsigned char T_crc = this->_i2c->read();

    this->T = ((uint16_t)T_h << 8) | ((uint16_t)T_l);
    if (!this->checkCRC(T, T_crc))
    {
        this->abort();
        return SHT4X_STATUS_CRC_FAIL;
    }
    this->TcrcOK = true;

    unsigned char RH_h = this->_i2c->read();
    unsigned char RH_l = this->_i2c->read();
    unsigned char RH_crc = this->_i2c->read();
    this->RH = ((uint16_t)RH_h << 8) | ((uint16_t)RH_l);
    if (!this->checkCRC(RH, RH_crc))
    {
        this->abort();
        return SHT4X_STATUS_CRC_FAIL;
    }
    this->RHcrcOK = true;

    this->_busy = false;
    return SHT4X_STATUS_OK;
}

/**
 * @brief  Compute temperature in degrees Celsius using raw data stored in the T property
 * @param  None
 * @retval  A floating point value representing temperature in degrees Celsius
 **/
float SHT4x::TtoDegC()
{
    return -45 + 175 * ((float)(this->T) / 65535);
}

/**
 * @brief  Compute temperature in degrees Fahrenheit using raw data stored in the T property
 * @param  None
 * @retval  A floating point value representing temperature in degrees Fahrenheit
 **/
float SHT4x::TtoDegF()
{
    return -49 + 315 * ((float)(this->T) / 65535);
}

/**
 * @brief  Compute relative humidity in percent using raw data stored in the RH property
 * @param  None
 * @retval  A floating point value representing relative humidity in percent
 **/
float SHT4x::RHtoPercent()
{
    return -6 + 125 * ((float)(this->RH) / 65535);
}
