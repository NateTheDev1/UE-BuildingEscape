// Nathaniel Richards 2021

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

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
}

void UOpenDoor::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (PressurePlate && OpeningActor && PressurePlate->IsOverlappingActor(OpeningActor))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	} else if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, OpenSpeed);
	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	// Door isn't even open yet
	if(CurrentYaw == InitialYaw)
	{
		return;
	}
	
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseSpeed);
	FRotator NewRotation = GetOwner()->GetActorRotation();
	NewRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(NewRotation);
}