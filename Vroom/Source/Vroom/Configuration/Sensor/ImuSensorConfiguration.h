#ifndef VROOM_ACCELEROMETERSENSORCONFIGURATION_H
#define VROOM_ACCELEROMETERSENSORCONFIGURATION_H

#include <rapidjson/document.h>

#include "Configuration/SensorConfiguration.h"

class ImuSensorConfiguration : public SensorConfiguration
{
	public:
		virtual ~ImuSensorConfiguration() {};
		virtual void Parse(const rapidjson::Value& document) override
		{
			SensorConfiguration::Parse(document);

			/*TODO: finish parsing*/
		}
};

#endif