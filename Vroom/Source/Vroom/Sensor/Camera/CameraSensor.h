#ifndef VROOM_CAMERASENSOR_H
#define VROOM_CAMERASENSOR_H

#include <memory>

#include "../Sensor.h"
#include "Types/Sensor/SensorReading.h"
#include "Types/Sensor/CameraSensorReading.h"
#include "Configuration/SensorConfiguration.h"
#include "Configuration/Sensor/CameraSensorConfiguration.h"

class CameraSensor : public Sensor
{
	public:
		CameraSensor(SensorConfiguration &configuration);

		virtual int GetUpdateRateMs() override { return this->_configuration.UpdateMsInterval; };

		void Configure(SensorConfiguration &configuration) override;
		std::shared_ptr<SensorReading> Get(bool saveToDisk);

	private:
		CameraSensorConfiguration _configuration;
};

#endif