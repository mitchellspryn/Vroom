#ifndef VROOM_IMUSENSOR_H
#define VROOM_IMUSENSOR_H

#include <memory>

#include "../Sensor.h"
#include "Types/Sensor/SensorReading.h"
#include "Types/Sensor/ImuSensorReading.h"
#include "Configuration/SensorConfiguration.h"
#include "Configuration/Sensor/ImuSensorConfiguration.h"

class ImuSensor : public Sensor
{
	public:
		ImuSensor(SensorConfiguration &configuration);

		virtual int GetUpdateRateMs() override { return this->_configuration.UpdateMsInterval; };

		void Configure(SensorConfiguration &configuration) override;
		std::shared_ptr<SensorReading> Get(bool saveToDisk);

	private:
		ImuSensorConfiguration _configuration;
};

#endif