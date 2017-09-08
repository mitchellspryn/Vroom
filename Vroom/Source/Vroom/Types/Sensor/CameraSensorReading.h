#ifndef VROOM_CAMERASENSORREADING_H
#define VROOM_CAMERASENSORREADING_H

#include "Utilities/SensorSerializationUtilities.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


class CameraSensorReading : public SensorReading
{
	public:
		virtual ~CameraSensorReading() {};
		cv::Mat Image;

		std::vector<std::pair<std::string, std::string>> GetSerializedProperties()
		{
			std::vector<std::pair<std::string, std::string>> data;
			data.push_back(std::pair<std::string, std::string>("Image", SensorSerializationUtilities::SerializeImage(this->Image)));
			return data;
		}
};


#endif