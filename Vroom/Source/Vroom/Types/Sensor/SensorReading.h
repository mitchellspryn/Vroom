#ifndef VROOM_SENSORREADING_H
#define VROOM_SENSORREADING_H

#include <vector>
#include <string>
#include <utility>

class SensorReading
{
	public:

		/*Get list of name-value pairs for serialization*/
		virtual std::vector<std::pair<std::string, std::string>> GetSerializedProperties() = 0;
};


#endif