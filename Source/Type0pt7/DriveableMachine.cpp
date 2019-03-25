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
//	for (int i = 0; i < HoeingTileLength; i++)
//	{
		for (int j = 0; j < HoeingTileWidth; j++)
		{
			const float pi = 3.1415926535f;
//			float YjCorrection = j*(FMath::Cos(-1.f*MachineRotation.Yaw*(pi/180.f)))* 100.f; 
//			float XjCorrection = j*(FMath::Sin(-1.f*(MachineRotation.Yaw *(pi/180.f))))* 100.f;

			float CosPhi = (FMath::Cos(-1.f*MachineRotation.Yaw*(pi/180.f))); 
			float SinPhi = (FMath::Sin(-1.f*(MachineRotation.Yaw *(pi/180.f))));
//+ (j *100.f) + 100.f *0.35 * j
			float CosCorrection = FMath::Cos(-1.f*MachineRotation.Yaw*(pi/180.f));
			float SinCorrection = FMath::Sin(-1.f*MachineRotation.Yaw*(pi/180.f));
			float RowOffsetX = (((HoeingTileWidth - 1.f) / 2.f) * 110.f*SinCorrection);
			float RowOffsetY = (((HoeingTileWidth - 1.f) / 2.f) * 110.f*CosCorrection);
			FVector ModifiedLocation = FVector(MachineLocation.X + (100.f*j * SinCorrection) - RowOffsetX , MachineLocation.Y + (j *100.f * CosCorrection) - RowOffsetY, 5.f);
			//FVector ModifiedLocation = FVector(MachineLocation.X + (100.f*j * FMath::Sin(-2.f*MachineRotation.Yaw * (pi/180.f))) , MachineLocation.Y + (j *100.f) - 100.f, 5.f);
		//	FVector ModifiedLocation = FVector(MachineLocation.X - (i * 100.f) + 300.f, MachineLocation.Y + (j *100.f) - 100.f, 5.f);
			

			//FVector ModifiedLocation = FVector(MachineLocation.X*CosPhi - MachineLocation.Y*SinPhi, MachineLocation.X*SinPhi + MachineLocation.Y*CosPhi + (j *100.f) - (((HoeingTileWidth - 1.f) / 2.f) * 100.f) , 5.f);
		//	FVector ModifiedLocation = FVector(MachineLocation.X + XjCorrection, MachineLocation.Y + (j *100.f) - YjCorrection/2.f - (((HoeingTileWidth - 1.f) / 2.f) * 100.f) , 5.f);
		//	FVector ModifiedLocation = FVector(MachineLocation.X + 100.f *0.7 * j, MachineLocation.Y + (j *100.f) - 100.f*0.35f*j - (((HoeingTileWidth - 1.f) / 2.f) * 100.f) , 5.f);
		//	FVector ModifiedLocation = FVector(MachineLocation.X + XjCorrection, MachineLocation.Y + YjCorrection +(j *100.f) - (((HoeingTileWidth - 1.f) / 2.f) * 100.f) , 5.f);
		//	FVector ModifiedLocation = FVector(MachineLocation.X - ((HoeingTileLength - 1.f) / 2.f * 100.f) + i * 100.f, MachineLocation.Y - ((HoeingTileWidth - 1.f) / 2.f * 100.f) + j * 100.f, 5.f);
			//UE_LOG(LogTemp, Error, TEXT("j: %i, XjCorrection = %f, YjCorrection = %f"), j, XjCorrection, YjCorrection);
			UE_LOG(LogTemp, Error, TEXT("ModifiedLocation: X = %f, Y = %f, X = %f"), ModifiedLocation.X, ModifiedLocation.Y, ModifiedLocation.Z);
			UE_LOG(LogTemp, Warning, TEXT("MachineRotation: Yaw: %f"),  MachineRotation.Yaw);
			UE_LOG(LogTemp, Warning, TEXT("Y: CosCorrection %f"),  CosCorrection);
			UE_LOG(LogTemp, Warning, TEXT("X: SinCorrection %f"),  SinCorrection);
			if (!ensure(LandManager)) { return; }
			if (!ensure(LandManager->HoedLandHISMC)) { return; }
			LandManager->PlaceLandTile(ModifiedLocation, MachineRotation);
		}
//	}
}

void ADriveableMachine::HoeWhileMoving()
{

}
