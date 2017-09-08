#ifndef VROOM_SENSORCONFIGURATION_H
#define VROOM_SENSORCONFIGURATION_H

#include <rapidjson/document.h>

#include <string>

class SensorConfiguration
{
	public:
		virtual ~SensorConfiguration() {};
		std::string Name;
		std::string Type;
		std::string OutputPath;
		int OutputMsInterval;
		int UpdateMsInterval;

		virtual void Parse(const rapidjson::Document& document)
		{

		}
};

#endif