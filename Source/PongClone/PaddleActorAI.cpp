// Fill out your copyright notice in the Description page of Project Settings.

#include "PaddleActorAI.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include <BallActor.h>

/** Basic game paddle AI which tracks the
    @ABallActor movement and sets its force accordingly */

const float PaddleSpeed = 700.0f;

// Sets default values
APaddleActorAI::APaddleActorAI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh and set its collision profile
	OurStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OurStaticMeshComponent->SetupAttachment(RootComponent);
	OurStaticMeshComponent->SetSimulatePhysics(true);
	OurStaticMeshComponent->SetCollisionProfileName(TEXT("Pawn"));

	RootComponent = OurStaticMeshComponent;
}

// Called when the game starts or when spawned
void APaddleActorAI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APaddleActorAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToBall();		
}

void APaddleActorAI::MoveToBall()
{
	if (Ball)
	{
		// Get the difference between my location and the ball's location
		FVector BallLocation = Ball->CurrentPosition;
		FVector MyLocation = OurStaticMeshComponent->GetComponentLocation();

		float Difference = BallLocation.X - MyLocation.X;

		FVector Force = FVector(Difference * PaddleSpeed, 0.0f, 0.0f);

		// DeltaTime is already applied on AddForce
		OurStaticMeshComponent->AddForce(Force);
	}
}

