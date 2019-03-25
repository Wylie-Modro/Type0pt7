// Fill out your copyright notice in the Description page of Project Settings.

#include "DriveableMachine.h"
#include "LandManager.h"

// Sets default values
ADriveableMachine::ADriveableMachine()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADriveableMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADriveableMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADriveableMachine::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADriveableMachine::StartUpHoe()
{
	FVector MachineLocation = this->GetActorLocation();
	FRotator MachineRotation = GetActorRotation();
	for (int i = 0; i < HoeingTileLength; i++)
	{
		for (int j = 0; j < HoeingTileWidth; j++)
		{
			const float pi = 3.1415926535f;
			
			float CosCorrection = FMath::Cos(-1.f*MachineRotation.Yaw*(pi/180.f));
			float SinCorrection = FMath::Sin(-1.f*MachineRotation.Yaw*(pi/180.f));

			float RowAdjustmentForAngle_XComp = (j * 100.f * SinCorrection);
			float RowAdjustmentForAngle_YComp = (j * 100.f * CosCorrection);

			float InitialRowOffset_XComp = ( -1.f * ((HoeingTileWidth - 1.f) / 2.f) * 110.f*SinCorrection);
			float InitialRowOffset_YComp = ( -1.f * ((HoeingTileWidth - 1.f) / 2.f) * 110.f*CosCorrection);

			float ColumnAdjustmentForAngle_XComp = (-1.f * i * 100.f *CosCorrection);
			float ColumnAdjustmentForAngle_YComp = (i * 100.f*SinCorrection);

			float InitialColumnOffset_XComp = (((HoeingTileLength - 1.f) / 2.f) * 110.f*CosCorrection);
			float InitialColumnOffset_YComp = ( -1.f * ((HoeingTileLength - 1.f) / 2.f) * 110.f*SinCorrection);

			FVector ModifiedLocation = FVector(MachineLocation.X + RowAdjustmentForAngle_XComp + InitialRowOffset_XComp + ColumnAdjustmentForAngle_XComp + InitialColumnOffset_XComp, MachineLocation.Y + RowAdjustmentForAngle_YComp + InitialRowOffset_YComp + ColumnAdjustmentForAngle_YComp + InitialColumnOffset_YComp, 5.f);

//			UE_LOG(LogTemp, Error, TEXT("ModifiedLocation: X = %f, Y = %f, X = %f"), ModifiedLocation.X, ModifiedLocation.Y, ModifiedLocation.Z);
//			UE_LOG(LogTemp, Warning, TEXT("MachineRotation: Yaw: %f"),  MachineRotation.Yaw);
//			UE_LOG(LogTemp, Warning, TEXT("Y: CosCorrection %f"),  CosCorrection);
//			UE_LOG(LogTemp, Warning, TEXT("X: SinCorrection %f"),  SinCorrection);

			if (!ensure(LandManager)) { return; }
			if (!ensure(LandManager->HoedLandHISMC)) { return; }
			LandManager->PlaceLandTile(ModifiedLocation, MachineRotation);
		}
	}
}

void ADriveableMachine::HoeWhileMoving()
{

}
