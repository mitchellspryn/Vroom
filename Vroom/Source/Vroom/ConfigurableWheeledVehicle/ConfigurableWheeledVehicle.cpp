// Fill out your copyright notice in the Description page of Project Settings.

#include "ConfigurableWheeledVehicle.h"

void AConfigurableWheeledVehicle::Reconfigure(const rapidjson::Value& json)
{
	ConfigurableWheeledVehicleConfiguration* configuration = static_cast<ConfigurableWheeledVehicleConfiguration*>(this->GetVehicleMovement());

	/*Set up global parameters*/
	if (json.HasMember("DeprecatedSpringOffsetMode") && json["DeprecatedSpringOffsetMode"].IsBool())
	{
		configuration->bDeprecatedSpringOffsetMode = (json["DeprecatedSpringOffsetMode"].GetBool() ? 0x01 : 0x00);
	}

	JsonUtilities::SetIfExists(&configuration->Mass, "Mass", json);

	JsonUtilities::SetIfExists(&configuration->DragCoefficient, "DragCoefficient", json);
	JsonUtilities::SetIfExists(&configuration->ChassisWidth, "ChassisWidth", json);
	JsonUtilities::SetIfExists(&configuration->ChassisHeight, "ChassisHeight", json);
	//JsonUtilities::SetIfExists(&configuration->bReverseAsBrake, "ReverseAsBreak", json); //We never want this on.
	JsonUtilities::SetIfExists(&configuration->EstimatedMaxEngineSpeed, "EstimatedMaxEngineSpeed", json);
	JsonUtilities::SetIfExists(&configuration->MaxEngineRPM, "MaxEngineRPM", json);
	JsonUtilities::SetIfExists(&configuration->MinNormalizedTireLoad, "MinNormalizedTireLoad", json);
	JsonUtilities::SetIfExists(&configuration->MaxNormalizedTireLoad, "MaxNormalizedTireLoad", json);
	JsonUtilities::SetIfExists(&configuration->MaxNormalizedTireLoadFiltered, "MaxNormalizedTireLoadFiltered", json);
	JsonUtilities::SetIfExists(&configuration->ThresholdLongitudinalSpeed, "ThresholdLongitudinalSpeed", json);
	JsonUtilities::SetIfExists(&configuration->LowForwardSpeedSubStepCount, "LowForwardSpeedSubStepCount", json);
	JsonUtilities::SetIfExists(&configuration->HighForwardSpeedSubStepCount, "HighForwardSpeedSubStepCount", json);
	JsonUtilities::SetIfExists(&configuration->AckermannAccuracy, "AckermannAccuracy", json);

	if (configuration->ChassisHeight > 0.0f && configuration->ChassisWidth > 0.0f)
	{
		configuration->DragArea = configuration->ChassisWidth * configuration->ChassisHeight;
	}

	/*Engine Setup*/
	if (json.HasMember("Engine"))
	{
		const rapidjson::Value& engineJson = json["Engine"];

		JsonUtilities::ParseRuntimeFloatCurveIfExists(
			configuration->EngineSetup.TorqueCurve,
			engineJson,
			"TorqueCurve");

		JsonUtilities::SetIfExists(&configuration->EngineSetup.MaxRPM, "MaxRPM", engineJson);
		JsonUtilities::SetIfExists(&configuration->EngineSetup.MOI, "MOI", engineJson);
		JsonUtilities::SetIfExists(&configuration->EngineSetup.DampingRateFullThrottle, "DampingRateFullThrottle", engineJson);
		JsonUtilities::SetIfExists(&configuration->EngineSetup.DampingRateZeroThrottleClutchEngaged, "DampingRateZeroThrottleClutchEngaged", engineJson);
		JsonUtilities::SetIfExists(&configuration->EngineSetup.DampingRateZeroThrottleClutchDisengaged, "DampingRageZeroThrottleClutchDisengaged", engineJson);

		configuration->UpdateEngineSetup(configuration->EngineSetup);
	}

	/*Differential4WD data*/
	if (json.HasMember("Differential4WD"))
	{
		const rapidjson::Value& diffJson = json["Differential4WD"];

		if (diffJson.HasMember("DifferentialType"))
		{
			ParseEVehicleDifferential4W(&configuration->DifferentialSetup.DifferentialType, diffJson["DifferentialType"].GetString());
		}

		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.FrontRearSplit, "FrontRearSplit", diffJson);
		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.FrontLeftRightSplit, "FrontLeftRightSplit", diffJson);
		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.RearLeftRightSplit, "RearLeftRightSplit", diffJson);
		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.CentreBias, "CenterBias", diffJson);
		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.FrontBias, "FrontBias", diffJson);
		JsonUtilities::SetIfExists(&configuration->DifferentialSetup.RearBias, "RearBias", diffJson);

		configuration->UpdateDifferentialSetup(configuration->DifferentialSetup);
	}

	/*Transmission data*/
	if (json.HasMember("Transmisson"))
	{
		const rapidjson::Value& transmissionJson = json["Transmission"];

		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.bUseGearAutoBox, "UseAutomaticTransmission", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.GearSwitchTime, "GearSwitchTime", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.GearAutoBoxLatency, "GearAutoBoxLatency", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.FinalRatio, "FinalRatio", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.ReverseGearRatio, "ReverseGearRatio", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.NeutralGearUpRatio, "NeutralGearUpRatio", transmissionJson);
		JsonUtilities::SetIfExists(&configuration->TransmissionSetup.ClutchStrength, "ClutchStrength", transmissionJson);

		if (transmissionJson.HasMember("Gears") && transmissionJson["Gears"].IsArray())
		{
			TArray<FVehicleGearData> newGears;
			for (const rapidjson::Value &gear : transmissionJson["Gears"].GetArray())
			{
				FVehicleGearData newGear;
				JsonUtilities::SetIfExists(&newGear.DownRatio, "DownRatio", gear);
				JsonUtilities::SetIfExists(&newGear.UpRatio, "UpRatio", gear);
				JsonUtilities::SetIfExists(&newGear.Ratio, "Ratio", gear);
				newGears.Add(newGear);
			}

			if (newGears.Num() > 0)
			{
				configuration->TransmissionSetup.ForwardGears = newGears;
			}
		}

		configuration->UpdateTransmissionSetup(configuration->TransmissionSetup);
	}

	/*Set steering curve*/
	JsonUtilities::ParseRuntimeFloatCurveIfExists(
		configuration->SteeringCurve,
		json,
		"SteeringCurve");
}

void AConfigurableWheeledVehicle::SetControlSignals(float throttle, float brake, float steeringAngleInDegrees)
{
	UWheeledVehicleMovementComponent* movement = this->GetVehicleMovement();
	movement->SetThrottleInput(throttle);
	movement->SetBrakeInput(brake);
	movement->SetSteeringInput(steeringAngleInDegrees);
}

void AConfigurableWheeledVehicle::ParseEVehicleDifferential4W(TEnumAsByte<EVehicleDifferential4W::Type>* configuration, const std::string differentialDriveStr)
{
	std::string differentialDriveStrLower = StringUtilities::ToLower(differentialDriveStr);
	if (!differentialDriveStrLower.compare("limitedslip_4w"))
	{
		*configuration = EVehicleDifferential4W::Type::LimitedSlip_4W;
	}
	else if (!differentialDriveStrLower.compare("limitedslip_frontdrive"))
	{
		*configuration = EVehicleDifferential4W::Type::LimitedSlip_FrontDrive;
	}
	else if (!differentialDriveStrLower.compare("limitedslip_reardrive"))
	{
		*configuration = EVehicleDifferential4W::Type::LimitedSlip_RearDrive;
	}
	else if (!differentialDriveStrLower.compare("open_4w"))
	{
		*configuration = EVehicleDifferential4W::Type::Open_4W;
	}
	else if (!differentialDriveStrLower.compare("open_frontdrive"))
	{
		*configuration = EVehicleDifferential4W::Type::Open_FrontDrive;
	}
	else if (!differentialDriveStrLower.compare("open_reardrive"))
	{
		*configuration = EVehicleDifferential4W::Type::Open_RearDrive;
	}
	else
	{
		throw std::runtime_error(("Unsupported EVehicleDifferential4W type: " + differentialDriveStr).c_str());
	}
}

