#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UWorldPosition::BeginPlay() {
  Super::BeginPlay();

  FString ObjectName = GetOwner()->GetName();
  UE_LOG(LogTemp, Warning, TEXT("Object Name is: %s"), *GetOwner()->GetName());
  FVector ObjectPosition = GetOwner()->GetActorLocation();

  UE_LOG(LogTemp, Warning, TEXT("Location for %s is: %s"), *ObjectName,
         *ObjectPosition.ToString());
}

// Called every frame
void UWorldPosition::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
