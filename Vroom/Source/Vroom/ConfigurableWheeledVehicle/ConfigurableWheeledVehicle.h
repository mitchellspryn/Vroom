// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //for some reason, UBT doesn't like include guards

#include "CoreMinimal.h"
#include "WheeledVehicle.h"

#include <vector>

#include "Types/CommunicableData.h"
#include "Configuration/ConfigurableWheeledVehicleConfiguration.h"
#include "Sensor/SensorManager.h"

/*this needs to come LAST*/
#include "ConfigurableWheeledVehicle.generated.h"

UCLASS()
class VROOM_API AConfigurableWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

	public:
		void Reconfigure(ConfigurableWheeledVehicleConfiguration configuration);
		void SetControlSignals(double throttle, double brake, double steeringAngleInDegrees);

	private:
		std::vector<std::function<void(CommunicableData)>> _listeners;
		SensorManager* _sensorManager;
};
