// Nathaniel Richards 2021

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();

public:
	// Called every frame
	virtual void
	TickComponent(const float DeltaTime, const ELevelTick TickType,
	              FActorComponentTickFunction* ThisTickFunction) override;
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

private:
	float InitialYaw;
	float CurrentYaw;

	float DoorLastOpened = 0.f;

	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;
		
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* OpeningActor;

	UPROPERTY(EditAnywhere)
	float CloseSpeed = 0.7f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* ReenterVolume;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;
};
