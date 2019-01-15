// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "WheelWithSuspension.generated.h"

UCLASS()
class TYPE0PT7_API AWheelWithSuspension : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWheelWithSuspension();

	float TotalForceMagnitudeThisFrame = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

	void ApplyForce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component") USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") USphereComponent* Axel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") UPhysicsConstraintComponent* MachineBaseToAxelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Component") UPhysicsConstraintComponent* AxelToWheelConstraint = nullptr;

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
