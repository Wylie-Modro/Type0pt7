// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandManager.generated.h"

class UHoedLandHISMC;

UCLASS()
class TYPE0PT7_API ALandManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandManager();

	virtual void Tick(float DeltaTime) override;

	void PlaceLandTile(FVector& Location, FRotator& Rotation);

	UPROPERTY(EditAnywhere, Category = "Hoeing")
	UHoedLandHISMC* HoedLandHISMC;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
