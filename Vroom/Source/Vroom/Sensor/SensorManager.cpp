#include "SensorManager.h"

SensorManager::SensorManager(std::vector<std::shared_ptr<SensorConfiguration>> sensorConfigurations, std::vector<std::function<void(CommunicableData)> > listenerFunctions)
{
	this->_listeners = listenerFunctions;

	/*TODO: There should be a factory method so that we can mock the clock for unit testing purposes*/
	this->_clock = static_cast<Clock*>(&HighResolutionClock::Get()); //TODO: This is kinda nasty

	for (size_t i = 0; i < sensorConfigurations.size(); ++i)
	{
		this->InitializeSensor(sensorConfigurations[i]);
	}

}

void SensorManager::Reconfigure(std::vector<std::shared_ptr<SensorConfiguration> > configuration)
{

}

void SensorManager::AddListener(std::function<void(CommunicableData)> listener)
{
	this->_listeners.push_back(listener);
}

void SensorManager::InitializeSensor(std::shared_ptr<SensorConfiguration> configuration)
{
	std::string sensorName = StringUtilities::ToLower(configuration->Name);
	std::string sensorType = StringUtilities::ToLower(configuration->Type);

	/*Check for null sensor name. This will conflict with the monitoring thread name*/
	if (sensorName.size() == 0)
	{
		throw std::runtime_error("Attempted to initialize a sensor without a name. This is disallowed. Please ensure that each sensor has a \"Name\" parameter set in the configuration json.");
	}

	/*Check to make sure we don't already have a sensor by this name initialized*/
	auto existingSensor = this->_sensors.find(sensorName);
	if (existingSensor != this->_sensors.end())
	{
		throw std::runtime_error("Attempted to re-initialize sensor of name " + sensorName + ". Currently, sensor names must be unique.");
	}


	Sensor* newSensor;
	if (sensorType == "camera")
	{
		newSensor = static_cast<Sensor*>(new CameraSensor(*configuration));
	}
	else if (sensorType == "imu")
	{
		newSensor = static_cast<Sensor*>(new ImuSensor(*configuration));
	}
	else if (sensorType == "lidar")
	{
		newSensor = static_cast<Sensor*>(new LidarSensor(*configuration));
	}
	else
	{
		throw std::runtime_error("Attempted to initialize sensor of type " + sensorType + ", which is not supported.");
	}

	this->_sensors.insert(std::make_pair(sensorName, newSensor));
}

void SensorManager::StartSensorCollection()
{
	this->StopSensorCollection();

	this->_isCollecting = true;

	int index = 0;
	for (auto it = this->_sensors.begin(); it != this->_sensors.end(); ++it)
	{
		std::thread* collectionThread = new std::thread(&SensorManager::SensorCollectionFunction, this, it->second, this->_clock, index);
		this->_collectionThreads.insert(std::make_pair(StringUtilities::ToLower(it->second->GetName()), collectionThread));
		this->_sensorReadingCache.push_back(nullptr);
		++index;
	}

	/*Add montitoring thread*/
	std::thread* monitoringThread = new std::thread(&SensorManager::SensorMonitoringFunction, this);
	this->_collectionThreads.insert(std::make_pair("", monitoringThread));
}

void SensorManager::StopSensorCollection()
{
	this->_isCollecting = false;

	for (auto it = this->_collectionThreads.begin(); it != this->_collectionThreads.end(); ++it)
	{
		if (it->second->joinable())
		{
			it->second->join();
		}
	}

	for (auto it = this->_collectionThreads.begin(); it != this->_collectionThreads.end(); ++it)
	{
		if (it->second != nullptr)
		{
			delete it->second;
		}
	}

	this->_collectionThreads.clear();
	this->_sensorReadingCache.clear();
}

void SensorManager::SensorCollectionFunction(Sensor* sensor, Clock* clock, int index)
{
	std::chrono::high_resolution_clock::time_point nextUpdateTime;
	do
	{
		/*Collect data*/
		nextUpdateTime = clock->GetCurrentTime() + std::chrono::milliseconds(sensor->GetUpdateRateMs());
		std::shared_ptr<SensorReading> currentReading = sensor->Get(true); //TODO: expose save to disk configuration
		this->_sensorReadingCache[index] = currentReading;
		std::this_thread::sleep_for(nextUpdateTime - clock->GetCurrentTime());

	} while (this->_isCollecting);

	/*TODO: Should sensors have a "finalize()" method?*/
}

void SensorManager::SensorMonitoringFunction()
{
	bool anySensorsReady = false;
	do
	{
		CommunicableData data;
		anySensorsReady = false;
		for (size_t i = 0; i < this->_sensorReadingCache.size(); ++i)
		{
			if (this->_sensorReadingCache[i] != nullptr)
			{
				data.SensorReadings.push_back(this->_sensorReadingCache[i]);
				this->_sensorReadingCache[i] = nullptr;
				anySensorsReady = true;
			}
		}

		if (anySensorsReady)
		{
			for (size_t i = 0; i < this->_listeners.size(); ++i)
			{
				this->_listeners[i](data);
			}
		}
	} while (this->_isCollecting && anySensorsReady);
}

