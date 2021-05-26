/* MIT License
 *
 * Copyright (c) 2019 - 2021 Andreas Merkle <web@blue-andi.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*******************************************************************************
    DESCRIPTION
*******************************************************************************/
/**
 * @brief  DHT11 sensor
 * @author Andreas Merkle <web@blue-andi.de>
 * 
 * @addtogroup hal
 *
 * @{
 */

#ifndef __SENSOR_DHT11_H__
#define __SENSOR_DHT11_H__

/******************************************************************************
 * Compile Switches
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <ISensor.hpp>
#include <SensorChannelType.hpp>
#include <DHTesp.h>

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Types and Classes
 *****************************************************************************/

/**
 * Temperature channel of the DHT11 sensor.
 */
class Dht11TemperatureChannel : public SensorChannelFloat32
{
public:

    /**
     * Constructs the temperature channel of the DHT11 sensor.
     * 
     * @param[in] dht   The DHT driver.
     */
    Dht11TemperatureChannel(DHTesp& dht) :
        m_dht(dht)
    {
    }

    /**
     * Destroys the temperature channel of the DHT11 sensor.
     */
    ~Dht11TemperatureChannel()
    {
    }

    /**
     * Get the kind of data and its unit.
     * 
     * @return Sensor data unit
     */
    DataWithUnit getDataWithUnit() const final
    {
        return ISensorChannel::DATA_TEMPERATURE_DEGREE_CELSIUS;
    }

    /**
     * Get data value.
     * 
     * @return Sensor data value
     */
    float getValue()
    {
        return m_dht.getTemperature();
    }

private:

    DHTesp& m_dht;  /**< DHT sensor driver. */

    Dht11TemperatureChannel();
    Dht11TemperatureChannel(const Dht11TemperatureChannel& channel);
    Dht11TemperatureChannel& operator=(const Dht11TemperatureChannel& channel);
};

/**
 * Humidity channel of the DHT11 sensor.
 */
class Dht11HumidityChannel : public SensorChannelFloat32
{
public:

    /**
     * Constructs the humidity channel of the DHT11 sensor.
     * 
     * @param[in] dht   The DHT driver.
     */
    Dht11HumidityChannel(DHTesp& dht) :
        m_dht(dht)
    {
    }

    /**
     * Destroys the humidity channel of the DHT11 sensor.
     */
    ~Dht11HumidityChannel()
    {
    }

    /**
     * Get the kind of data and its unit.
     * 
     * @return Sensor data unit
     */
    DataWithUnit getDataWithUnit() const final
    {
        return ISensorChannel::DATA_HUMIDITY_PERCENT;
    }

    /**
     * Get data value.
     * 
     * @return Sensor data value
     */
    float getValue()
    {
        return m_dht.getHumidity();
    }

private:

    DHTesp& m_dht;  /**< DHT sensor driver. */

    Dht11HumidityChannel();
    Dht11HumidityChannel(const Dht11HumidityChannel& channel);
    Dht11HumidityChannel& operator=(const Dht11HumidityChannel& channel);
};

/**
 * DHT11 sensor adapter
 */
class SensorDht11 : public ISensor
{
public:

    /**
     * Constructs the DHT11 sensor.
     */
    SensorDht11() :
        m_dht(),
        m_temperatureChannel(m_dht),
        m_humidityChannel(m_dht)
    {
    }

    /**
     * Destroys the DHT11 sensor.
     */
    ~SensorDht11()
    {
    }

    /**
     * Configures the sensor, so it is able to provide sensor data.
     */
    void begin() final;

    /**
     * Get number of data channels.
     * 
     * @return Number of data channels.
     */
    uint8_t getNumChannels() const final
    {
        return CHANNEL_ID_COUNT;
    }

    /**
     * Get data channel by index.
     * 
     * @return Data channel
     */
    ISensorChannel* getChannel(uint8_t index) final;

private:

    /**
     * Channel id
     */
    enum ChannelId
    {
        CHANNEL_ID_TEMPERATURE = 0, /**< Temperature channel id */
        CHANNEL_ID_HUMIDITY,        /**< Humidity channel id */
        CHANNEL_ID_COUNT            /**< Number of channels */
    };

    DHTesp                  m_dht;                  /**< DHT sensor driver. */
    Dht11TemperatureChannel m_temperatureChannel;   /**< Temperature channel */
    Dht11HumidityChannel    m_humidityChannel;      /**< Humidity channel */
    
};

/******************************************************************************
 * Functions
 *****************************************************************************/

#endif  /* __SENSOR_DHT11_H__ */

/** @} */