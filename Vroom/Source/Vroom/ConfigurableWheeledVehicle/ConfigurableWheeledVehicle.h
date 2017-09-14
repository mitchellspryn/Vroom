// Fill out your copyright notice in the Description page of Project Settings.

#pragma once //for some reason, UBT doesn't like include guards

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "WheeledVehicleMovementComponent4W.h"

#include <vector>

#include "Configuration/ConfigurableWheeledVehicleConfiguration.h"
#include "Sensor/SensorManager.h"
#include "Types/CommunicableData.h"
#include "Utilities/JsonUtilities.h"

/*this needs to come LAST*/
#include "ConfigurableWheeledVehicle.generated.h"

UCLASS()
class VROOM_API AConfigurableWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

	public:
		void Reconfigure(const rapidjson::Value &json);
		void SetControlSignals(float throttle, float brake, float steeringAngleInDegrees);

	private:
		void AConfigurableWheeledVehicle::ParseEVehicleDifferential4W(TEnumAsByte<EVehicleDifferential4W::Type>* configuration, const std::string differentialDriveStr);

		std::vector<std::function<void(CommunicableData)>> _listeners;
		SensorManager* _sensorManager;
};
