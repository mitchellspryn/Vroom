#ifndef VROOM_LIDARSENSORREADING_H
#define VROOM_LIDARSENSORREADING_H

#include "LidarPoint.h"
#include "SensorReading.h"
#include "Utilities/SensorSerializationUtilities.h"

#include <fstream>
#include <vector>


class LidarSensorReading : public SensorReading
{
	public:
		virtual ~LidarSensorReading() {};
		/*The xyz points of the lidar scan, considering the origin of the lidar as (0,0,0)*/
		std::vector<LidarPoint> LidarScan;

		/*The offset of the lidar from the origin of the car*/
		Eigen::Vector3d OriginOffset;

		std::vector<std::pair<std::string, std::string>> GetSerializedProperties() override
		{
			std::vector<std::pair<std::string, std::string>> data;
			data.push_back(std::pair<std::string, std::string>("OriginOffset", SensorSerializationUtilities::SerializeVector3d(this->OriginOffset)));
			data.push_back(std::pair<std::string, std::string>("Scan", SensorSerializationUtilities::SerializePointCloud(this->LidarScan)));
			return data;
		}
};

#endif