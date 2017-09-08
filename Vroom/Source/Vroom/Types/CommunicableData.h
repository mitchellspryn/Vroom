#ifndef VROOM_COMMUNICABLEDATA_H
#define VROOM_COMMUNICABLEDATA_H

#include <memory>
#include <vector>

#include "Sensor/SensorReading.h"
#include "Map/MapSegment.h"
#include "VehicleState.h"

/*Represents data that will communicated to external clients on a regular cadence*/
class CommunicableData
{
	public:
		std::vector<std::shared_ptr<SensorReading>> SensorReadings;
		VehicleState VehicleState;
		MapSegment MapSegment;
};

#endif