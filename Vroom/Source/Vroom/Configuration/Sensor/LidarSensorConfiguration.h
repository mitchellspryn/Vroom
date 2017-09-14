#ifndef VROOM_LIDARSENSORCONFIGURATION_H
#define VROOM_LIDARSENSORCONFIGURATION_H

#include <rapidjson/document.h>

class LidarSensorConfiguration : public SensorConfiguration
{
	public:
		virtual ~LidarSensorConfiguration() {};
		double HorizontalDegreesPerScan;
		double HorizontalRange;
		double VerticalDegreesPerScan;
		double VerticalRange;

		virtual void Parse(const rapidjson::Value& document) override
		{
			SensorConfiguration::Parse(document);

			/*TODO: finish parsing*/
		}
};

#endif