// Nathaniel Richards 2021

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

UOpenDoor::UOpenDoor() { PrimaryComponentTick.bCanEverTick = true; }

void UOpenDoor::BeginPlay() {

  Super::BeginPlay();

  //   FRotator CurrentRotation = GetOwner()->GetActorRotation();
  //   CurrentRotation.Yaw = 90.f;

  FRotator OpenDoor = {0.f, 90.f, 0.f};

  GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType,
                              FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}
