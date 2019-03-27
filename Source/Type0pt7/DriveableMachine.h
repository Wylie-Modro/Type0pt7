// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DriveableMachine.generated.h"

class ALandManager;

UCLASS()
class TYPE0PT7_API ADriveableMachine : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADriveableMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void StartUpHoe();

	UFUNCTION(BlueprintCallable)
	void ShutdownHoe();

	UPROPERTY(EditDefaultsOnly, Category = "Hoeing")
	int HoeingTileWidth = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Hoeing")
	int HoeingTileLength = 5;

	UPROPERTY(EditAnywhere, Category = "Hoeing")
	ALandManager* LandManager;

	void SetHoeState(bool val);

	UFUNCTION(BlueprintCallable)
	bool GetHoeState();

private:
	void HoeWhileMoving();

	bool HoeState = false;

	FVector PositionOfLastBlockPlaced;
};
