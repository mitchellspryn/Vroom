#ifndef VROOM_IMUSENSORREADING_H
#define VROOM_IMUSENSORREADING_H

#include "Utilities/SensorSerializationUtilities.h"

#include <Eigen/Dense>

class ImuSensorReading : public SensorReading
{
	public:
		Eigen::Vector3d MagneticField;
		Eigen::Vector3d Acceleration;
		Eigen::Vector3d AngularVelocity;

		std::vector<std::pair<std::string, std::string>> GetSerializedProperties() override
		{
			std::vector<std::pair<std::string, std::string>> data;
			data.push_back(std::pair<std::string, std::string>("MagneticField", SensorSerializationUtilities::SerializeVector3d(this->MagneticField)));
			data.push_back(std::pair<std::string, std::string>("Acceleration", SensorSerializationUtilities::SerializeVector3d(this->Acceleration)));
			data.push_back(std::pair<std::string, std::string>("AngularVelocity", SensorSerializationUtilities::SerializeVector3d(this->AngularVelocity)));
			return data;
		}
};

#endif