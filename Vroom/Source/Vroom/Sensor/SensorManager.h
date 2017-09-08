#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <chrono>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <thread>
#include <vector>

#include "Configuration/SensorConfiguration.h"
#include "Sensor.h"
#include "Lidar/LidarSensor.h"
#include "Imu/ImuSensor.h"
#include "Camera/CameraSensor.h"
#include "Types/Sensor/SensorReading.h"
#include "Types/CommunicableData.h"
#include "Utilities/Clock/Clock.h"
#include "Utilities/Clock/HighResolutionClock.h"
#include "Utilities/StringUtilities.h"

class SensorManager
{
	public:
		SensorManager(std::vector<std::shared_ptr<SensorConfiguration>> configuration, std::vector<std::function<void(CommunicableData)> > listenerFunctions);
		
		/*This cannot be used to create new sensors, only modify existing sensors*/
		void Reconfigure(std::vector<std::shared_ptr<SensorConfiguration> > configuration);
		void AddListener(std::function<void(CommunicableData)> listener);


	private:
		bool _isCollecting;
		std::unordered_map<std::string, std::thread*> _collectionThreads;
		std::vector<std::function<void(CommunicableData)> > _listeners;
		std::unordered_map<std::string, Sensor*> _sensors;
		std::vector<std::shared_ptr<SensorReading> > _sensorReadingCache;
		Clock* _clock;

		void InitializeSensor(std::shared_ptr<SensorConfiguration> configuration);
		void StartSensorCollection();
		void StopSensorCollection();

		void SensorCollectionFunction(Sensor* Sensor, Clock* clock, int index);
		void SensorMonitoringFunction();

};

#endif