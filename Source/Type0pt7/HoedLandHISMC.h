// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "HoedLandHISMC.generated.h"

/**
 * 
 */

class ADriveableMachine;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TYPE0PT7_API UHoedLandHISMC : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	UHoedLandHISMC();

	UFUNCTION(BlueprintCallable)
	void SpawnHoedTiles(FVector& Location, FRotator& Rotation);

	virtual void BeginPlay() override;
};
