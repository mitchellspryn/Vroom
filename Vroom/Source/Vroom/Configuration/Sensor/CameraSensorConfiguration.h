#ifndef VROOM_CAMERASENSORCONFIGURATION_H
#define VROOM_CAMERASENSORCONFIGURATION_H

#include <rapidjson/document.h>

#include "Configuration/SensorConfiguration.h"
#include "Configuration/Sensor/CameraOutputType.h"

class CameraSensorConfiguration : public SensorConfiguration
{
	public:
		virtual ~CameraSensorConfiguration() {};
		int ImageWidth;
		int ImageHeight;
		CameraOutputType OutputType;

		virtual void Parse(const rapidjson::Document& document) override
		{
			SensorConfiguration::Parse(document);

			/*TODO: finish parsing*/
		}
};

#endif