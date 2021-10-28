// Nathaniel Richards 2021

#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

#define OUT

UOpenDoor::UOpenDoor() { PrimaryComponentTick.bCanEverTick = true; }

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no pressure plate set"),
		       *GetOwner()->GetName());
	}

	OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();

	FindAudioComponent();
}

void UOpenDoor::TickComponent(const float DeltaTime, const ELevelTick TickType,
                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (TotalMassOfActors() >= MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio componernt!"), *GetOwner()->GetName());
	}
}


void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpenSpeed);
	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);

	CloseDoorSound = false;
	if(!AudioComponent) {return;}

	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
	
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// Door isn't even open yet
	if (CurrentYaw == InitialYaw)
	{
		return;
	}

	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseSpeed);
	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);

	OpenDoorSound = false;
	if (!AudioComponent) { return; }
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverLappingActors;

	// Find all overlapping actors

	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	for (const AActor* Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass is: %f"), TotalMass);
	}

	return TotalMass;
}
