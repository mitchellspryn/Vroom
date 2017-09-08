#include "LidarSensor.h"

LidarSensor::LidarSensor(SensorConfiguration& configuration)
{
	this->_configuration = static_cast<LidarSensorConfiguration&>(configuration);
}

void LidarSensor::Configure(SensorConfiguration &configuration)
{
	auto cast_configuration = static_cast<LidarSensorConfiguration&>(configuration);

	/*TODO: Merge with existing configuration*/
}

std::shared_ptr<SensorReading> LidarSensor::Get(bool saveToDisk)
{
	/*TODO: Implement me!*/
	std::shared_ptr<SensorReading> ptr;
	return ptr;
}
