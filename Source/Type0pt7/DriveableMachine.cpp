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

	HoeWhileMoving();
}

// Called to bind functionality to input
void ADriveableMachine::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADriveableMachine::SetHoeState(bool val)
{
	HoeState = val;
}

bool ADriveableMachine::GetHoeState()
{
	return HoeState;
}

void ADriveableMachine::EvaluateBlockOffsets(FRotator MachineRotation)
{

	CosCorrection = FMath::Cos(-1.f*MachineRotation.Yaw*(MY_PI / 180.f));
	SinCorrection = FMath::Sin(-1.f*MachineRotation.Yaw*(MY_PI / 180.f));

	InitialRowOffset_XComp = (-1.f * ((HoeingTileWidth - 1.f) / 2.f) * DIRT_BLOCK_SIZE * SinCorrection);
	InitialRowOffset_YComp = (-1.f * ((HoeingTileWidth - 1.f) / 2.f) * DIRT_BLOCK_SIZE * CosCorrection);

	InitialColumnOffset_XComp = (((HoeingTileLength - 1.f) / 2.f) * DIRT_BLOCK_SIZE * CosCorrection);  
	InitialColumnOffset_YComp = (-1.f * ((HoeingTileLength - 1.f) / 2.f) * DIRT_BLOCK_SIZE * SinCorrection);
}


void ADriveableMachine::StartUpHoe()
{
	FVector MachineLocation = this->GetActorLocation();
	FRotator MachineRotation = GetActorRotation();

	SetHoeState(true);

	for (int i = HoeingTileLength - 1; i >= 0; i--)
	{
		for (int j = HoeingTileWidth - 1; j >= 0; j--)
		{

			EvaluateBlockOffsets(MachineRotation);

			float RowAdjustmentForAngle_XComp = (j * DIRT_BLOCK_SIZE * ROW_GAP_FUDGE_FACTOR * SinCorrection);
			float RowAdjustmentForAngle_YComp = (j * DIRT_BLOCK_SIZE * ROW_GAP_FUDGE_FACTOR * CosCorrection);

			float ColumnAdjustmentForAngle_XComp = (-1.f * i * DIRT_BLOCK_SIZE * CosCorrection);
			float ColumnAdjustmentForAngle_YComp = (i * DIRT_BLOCK_SIZE * SinCorrection);

			FVector ModifiedLocation = FVector(MachineLocation.X + RowAdjustmentForAngle_XComp + InitialRowOffset_XComp + ColumnAdjustmentForAngle_XComp + InitialColumnOffset_XComp, MachineLocation.Y + RowAdjustmentForAngle_YComp + InitialRowOffset_YComp + ColumnAdjustmentForAngle_YComp + InitialColumnOffset_YComp, 5.f);

			if (!ensure(LandManager)) { return; }
			if (!ensure(LandManager->HoedLandHISMC)) { return; }
			LandManager->PlaceLandTile(ModifiedLocation, MachineRotation);
			PositionOfLastBlockPlaced = ModifiedLocation;
		}
	}
}

void ADriveableMachine::HoeWhileMoving()
{
	if (GetHoeState())
	{
		FVector MachineLocation = this->GetActorLocation();
		FRotator MachineRotation = GetActorRotation();

		EvaluateBlockOffsets(MachineRotation);

		FVector CurrentPositionOfHoeFront = FVector(MachineLocation.X + InitialRowOffset_XComp + InitialColumnOffset_XComp, MachineLocation.Y + InitialRowOffset_YComp + InitialColumnOffset_YComp, 5.f);

		float AmountMovedSinceLastPlacementX = FMath::Abs( FMath::Abs(CurrentPositionOfHoeFront.X) - FMath::Abs(PositionOfLastBlockPlaced.X) );
		float AmountMovedSinceLastPlacementY = FMath::Abs( FMath::Abs(CurrentPositionOfHoeFront.Y) - FMath::Abs(PositionOfLastBlockPlaced.Y) );

		if (AmountMovedSinceLastPlacementX >= DIRT_BLOCK_SIZE/2.f || AmountMovedSinceLastPlacementY >= DIRT_BLOCK_SIZE/2.f) 
		// Having a limit of DIRT_BLOCK_SIZE/2.f will spawn more blocks than is needed but till stop gaps between rows. Likely due to acceleration
		{

			for (int j = HoeingTileWidth - 1; j >= 0; j--)
			{
				float RowAdjustmentForAngle_XComp = (j * DIRT_BLOCK_SIZE * ROW_GAP_FUDGE_FACTOR * SinCorrection);
				float RowAdjustmentForAngle_YComp = (j * DIRT_BLOCK_SIZE * ROW_GAP_FUDGE_FACTOR * CosCorrection);

				FVector ModifiedLocation = FVector(MachineLocation.X + RowAdjustmentForAngle_XComp + InitialRowOffset_XComp + InitialColumnOffset_XComp, MachineLocation.Y + RowAdjustmentForAngle_YComp + InitialRowOffset_YComp + InitialColumnOffset_YComp, 5.f);

				if (!ensure(LandManager)) { return; }
				if (!ensure(LandManager->HoedLandHISMC)) { return; }
				LandManager->PlaceLandTile(ModifiedLocation, MachineRotation);
				PositionOfLastBlockPlaced = ModifiedLocation;

			}
		}
	}
}

void ADriveableMachine::ShutdownHoe()
{
	SetHoeState(false);
}
