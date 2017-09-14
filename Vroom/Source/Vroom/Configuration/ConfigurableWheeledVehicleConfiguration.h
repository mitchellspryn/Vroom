#ifndef VROOM_CONFIGURABLEWHEELEDVEHICLECONFIGURATION_H
#define VROOM_CONFIGURABLEWHEELEDVEHICLECONFIGURATION_H

#include <rapidjson/document.h>
#include "WheeledVehicleMovementComponent4W.h"

class ConfigurableWheeledVehicleConfiguration : public UWheeledVehicleMovementComponent4W
{
	public:
		void UpdateEngineSetup(const FVehicleEngineData& newEngineSetup)
		{
			UWheeledVehicleMovementComponent4W::UpdateEngineSetup(newEngineSetup);
		}

		void UpdateDifferentialSetup(const FVehicleDifferential4WData& newDifferentialSetup)
		{
			UWheeledVehicleMovementComponent4W::UpdateDifferentialSetup(newDifferentialSetup);
		}

		void UpdateTransmissionSetup(const FVehicleTransmissionData& newGearSetup)
		{
			UWheeledVehicleMovementComponent4W::UpdateTransmissionSetup(newGearSetup);
		}
};

#endif