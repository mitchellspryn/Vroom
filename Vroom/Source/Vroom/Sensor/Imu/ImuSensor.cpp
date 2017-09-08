#include "ImuSensor.h"

ImuSensor::ImuSensor(SensorConfiguration& configuration)
{
	this->_configuration = static_cast<ImuSensorConfiguration&>(configuration);
}

void ImuSensor::Configure(SensorConfiguration &configuration)
{
	auto cast_configuration = static_cast<ImuSensorConfiguration&>(configuration);

	/*TODO: Merge with existing configuration*/
}

std::shared_ptr<SensorReading> ImuSensor::Get(bool saveToDisk)
{
	/*TODO: Implement me!*/
	std::shared_ptr<SensorReading> ptr;
	return ptr;
}
