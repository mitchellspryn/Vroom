#ifndef VROOM_SENSOR_H
#define VROOM_SENSOR_H

#include <string>
#include <memory>

#include "Types/Sensor/SensorReading.h"
#include "Configuration/SensorConfiguration.h"

class Sensor
{
	public:
		virtual ~Sensor() {};

		/*Configures the sensor given a configuration object*/
		virtual void Configure(SensorConfiguration &configuration) = 0;

		virtual std::string GetName() { return this->_name; };
		virtual int GetUpdateRateMs() = 0;
		
		/*Gets a sensor reading.*/
		/*If saveToDisk is true, saves this reading to disk in addition to returning the object*/
		virtual std::shared_ptr<SensorReading> Get(bool saveToDisk) = 0;

	protected:
		std::string _name;
};

#endif