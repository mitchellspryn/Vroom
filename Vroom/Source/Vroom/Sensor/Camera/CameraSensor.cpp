#include "CameraSensor.h"

#include <vector>

CameraSensor::CameraSensor(SensorConfiguration& configuration)
{
	this->_configuration = static_cast<CameraSensorConfiguration&>(configuration);

}

void CameraSensor::Configure(SensorConfiguration &configuration)
{
	auto cast_configuration = static_cast<CameraSensorConfiguration&>(configuration);

	/*TODO: Merge with existing configuration*/
}

std::shared_ptr<SensorReading> CameraSensor::Get(bool saveToDisk)
{
	/*TODO: Implement me!*/
	std::shared_ptr<SensorReading> ptr;
	return ptr;
}
