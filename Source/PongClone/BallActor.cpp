// Fill out your copyright notice in the Description page of Project Settings.

#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include <ScoreTriggerBox.h>

/** Game ball, which listens for overlapping with @ScoreTriggerBox
  and resets its own position when out of bounds. For further
  development there should be a delay before resetting the ball again. */

const float PushForce = 1500.0f;

// Sets default values
ABallActor::ABallActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh and set its collision profile
	OurStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OurStaticMeshComponent->SetupAttachment(RootComponent);
	OurStaticMeshComponent->SetSimulatePhysics(true);
	OurStaticMeshComponent->SetNotifyRigidBodyCollision(true);
	OurStaticMeshComponent->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = OurStaticMeshComponent;

	// Create a trigger to listen when ball goes out of bounds
	OurCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColSphere"));
	OurCollisionSphere->InitSphereRadius(25.0f);
	OurCollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
	OurCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABallActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();

	PushX();
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update the current position variable
	CurrentPosition = OurStaticMeshComponent->GetComponentLocation();
}

// Push the ball in X axis
void ABallActor::PushX()
{
	FVector Velocity = FVector(0.0f, PushForce, 0.0f);
	OurStaticMeshComponent->SetPhysicsLinearVelocity(Velocity);
}

// Reset the position & push again
void ABallActor::Reset()
{
	OurStaticMeshComponent->SetRelativeLocation(FVector::ZeroVector);

	PushX();
}

// Listen for overlap with score box
void ABallActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		// Make sure we are hitting a score trigger
		if (OtherActor->IsA(AScoreTriggerBox::StaticClass())) 
		{
			Reset();
		}		
	}
}


