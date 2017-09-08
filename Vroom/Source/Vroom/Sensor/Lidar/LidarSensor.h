#ifndef VROOM_LIDARSENSOR_H
#define VROOM_LIDARSENSOR_H

#include <memory.h>

#include "../Sensor.h"
#include "Types/Sensor/SensorReading.h"
#include "Types/Sensor/LidarSensorReading.h"
#include "Configuration/SensorConfiguration.h"
#include "Configuration/Sensor/LidarSensorConfiguration.h"

class LidarSensor : public Sensor
{
	public:
		LidarSensor(SensorConfiguration &configuration);

		virtual int GetUpdateRateMs() override { return this->_configuration.UpdateMsInterval; };

		void Configure(SensorConfiguration &configuration) override;
		std::shared_ptr<SensorReading> Get(bool saveToDisk);

	private:
		LidarSensorConfiguration _configuration;

};

#endif