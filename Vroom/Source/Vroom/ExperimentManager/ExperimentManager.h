// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Communication/ExternalProcessCommunicator.h"
#include "ConfigurableWheeledVehicle/ConfigurableWheeledVehicle.h"
#include "MapGeneration/MapGenerator.hpp"

/*This must come LAST*/
#include "ExperimentManager.generated.h"

UCLASS()
class VROOM_API AExperimentManager : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		AExperimentManager();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:	
		AConfigurableWheeledVehicle* _userVehicle;
		ExternalProcessCommunicator* _externalProcessCommunicator;
		MapGenerator* _mapGenerator;


	
};
