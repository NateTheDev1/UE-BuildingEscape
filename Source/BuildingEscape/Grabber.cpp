// Nathaniel Richards 2021

#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Math/Color.h"
#include "Grabber.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error,
		       TEXT("No physics handle component found on %s"),
		       *GetOwner()->GetName()
		);
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error,
		       TEXT("No input component found on %s"),
		       *GetOwner()->GetName()
		);
	} else
	{
		// Right mouse key or E
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	const FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewLocation,
		LineTraceEnd, FColor::Cyan,
		false,
		0.f,
		0,
		5.f
	);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("The actor that was hit was:  %s"), *HitActor->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab action was triggerred"));
}
