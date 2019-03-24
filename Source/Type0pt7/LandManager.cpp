// Fill out your copyright notice in the Description page of Project Settings.

#include "LandManager.h"
#include "HoedLandHISMC.h"

// Sets default values
ALandManager::ALandManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoedLandHISMC = CreateDefaultSubobject<UHoedLandHISMC>("HoedLandHISMComponent");

}

// Called when the game starts or when spawned
void ALandManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALandManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALandManager::PlaceLandTile(FVector& Location, FRotator& Rotation)
{
	if (!ensure(HoedLandHISMC)) { return; }
	HoedLandHISMC->SpawnHoedTiles(Location, Rotation);
}
