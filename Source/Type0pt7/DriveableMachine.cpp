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

void ADriveableMachine::StartUpHoe()
{
	FVector MachineLocation = this->GetActorLocation();
	FRotator MachineRotation = GetActorRotation();

	SetHoeState(true);

	for (int i = HoeingTileLength - 1; i >= 0; i--)
	{
		for (int j = HoeingTileWidth - 1; j >= 0; j--)
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

		const float pi = 3.1415926535f;
		float CosCorrection = FMath::Cos(-1.f*MachineRotation.Yaw*(pi / 180.f));
		float SinCorrection = FMath::Sin(-1.f*MachineRotation.Yaw*(pi / 180.f));

		float InitialRowOffset_XComp = (-1.f * ((HoeingTileWidth - 1.f) / 2.f) * 100.f*SinCorrection);
		float InitialRowOffset_YComp = (-1.f * ((HoeingTileWidth - 1.f) / 2.f) * 100.f*CosCorrection);

		float InitialColumnOffset_XComp = (((HoeingTileLength - 1.f) / 2.f) * 90.f*CosCorrection);
		float InitialColumnOffset_YComp = (-1.f * ((HoeingTileLength - 1.f) / 2.f) * 90.f*SinCorrection);

		FVector CurrentPositionOfHoeFront = FVector(MachineLocation.X + InitialRowOffset_XComp + InitialColumnOffset_XComp, MachineLocation.Y + InitialRowOffset_YComp + InitialColumnOffset_YComp, 5.f);

		UE_LOG(LogTemp, Warning, TEXT("PositionOfLastBlockPlaced: X:%f, Y:%f"),  PositionOfLastBlockPlaced.X, PositionOfLastBlockPlaced.Y);
		UE_LOG(LogTemp, Warning, TEXT("CurrentPositionOfHoeFront: X:%f, Y:%f"),  CurrentPositionOfHoeFront.X, CurrentPositionOfHoeFront.Y);

		float AmountMovedSinceLastPlacementX = FMath::Abs( FMath::Abs(CurrentPositionOfHoeFront.X) - FMath::Abs(PositionOfLastBlockPlaced.X) );
		float AmountMovedSinceLastPlacementY = FMath::Abs( FMath::Abs(CurrentPositionOfHoeFront.Y) - FMath::Abs(PositionOfLastBlockPlaced.Y) );
		//float AmountMovedSinceLastPlacement = FMath::Abs( FMath::Sqrt(FMath::Pow(CurrentPositionOfHoeFront.X, 2) + FMath::Pow(CurrentPositionOfHoeFront.Y, 2)) - FMath::Sqrt(FMath::Pow(PositionOfLastBlockPlaced.X, 2) + FMath::Pow(PositionOfLastBlockPlaced.Y, 2)));

		//float AmountMovedSinceLastPlacement = CurrentPositionOfHoeFront.X - PositionOfLastBlockPlaced.X;
		UE_LOG(LogTemp, Warning, TEXT("AmountMovedSinceLastPlacementX: %f"),  AmountMovedSinceLastPlacementX);
		UE_LOG(LogTemp, Warning, TEXT("AmountMovedSinceLastPlacementY: %f"),  AmountMovedSinceLastPlacementY);

		if (AmountMovedSinceLastPlacementX >= 50.f || AmountMovedSinceLastPlacementY >= 50.f) // having value of 50 will spawn more than needed but till stop row segmentation. Likely due to acceleration
		{

			for (int j = HoeingTileWidth - 1; j >= 0; j--)
			{
				float RowAdjustmentForAngle_XComp = (j * 90.f * SinCorrection);
				float RowAdjustmentForAngle_YComp = (j * 90.f * CosCorrection);

				FVector ModifiedLocation = FVector(MachineLocation.X + RowAdjustmentForAngle_XComp + InitialRowOffset_XComp + InitialColumnOffset_XComp, MachineLocation.Y + RowAdjustmentForAngle_YComp + InitialRowOffset_YComp + InitialColumnOffset_YComp, 5.f);

				if (!ensure(LandManager)) { return; }
				if (!ensure(LandManager->HoedLandHISMC)) { return; }
				LandManager->PlaceLandTile(ModifiedLocation, MachineRotation);
				PositionOfLastBlockPlaced = ModifiedLocation;

				UE_LOG(LogTemp, Warning, TEXT("Blocks Placed!"));
			}
		}
	}
}

void ADriveableMachine::ShutdownHoe()
{
	SetHoeState(false);
}
