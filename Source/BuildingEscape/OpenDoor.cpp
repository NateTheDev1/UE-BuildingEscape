// Nathaniel Richards 2021

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

UOpenDoor::UOpenDoor() { PrimaryComponentTick.bCanEverTick = true; }

void UOpenDoor::BeginPlay() {
  Super::BeginPlay();
  InitialYaw = GetOwner()->GetActorRotation().Yaw;
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType,
                              FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  //   float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

  //   FRotator OpenDoor(0.f, TargetYaw, 0.f);
  //   OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);

  //   GetOwner()->SetActorRotation(OpenDoor);
}
