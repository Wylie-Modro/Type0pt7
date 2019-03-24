// Fill out your copyright notice in the Description page of Project Settings.

#include "WheelWithSuspension.h"

// Sets default values
AWheelWithSuspension::AWheelWithSuspension()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MachineBaseToAxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MachineBaseToAxelConstraint"));
	SetRootComponent(MachineBaseToAxelConstraint);


	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(RootComponent);

	AxelToWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxelToWheelConstraint"));
	AxelToWheelConstraint->SetupAttachment(Axel);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);


}

// Called when the game starts or when spawned
void AWheelWithSuspension::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &AWheelWithSuspension::OnHit);

	auto MachineActor = GetAttachParentActor();
	if (MachineActor)
	{
		MachineBaseToAxelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(MachineActor->GetRootComponent()), NAME_None, Axel, NAME_None);
		AxelToWheelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MachineActor was null"));
	}

}

// Called every frame
void AWheelWithSuspension::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}

}

void AWheelWithSuspension::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void AWheelWithSuspension::ApplyForce()
{
//	UE_LOG(LogTemp, Warning, TEXT("Force Being Applied This Frame: %f"), TotalForceMagnitudeThisFrame);
	Wheel->AddForce(Axel->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void AWheelWithSuspension::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}
