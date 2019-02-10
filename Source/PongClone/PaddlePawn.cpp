#include "PaddlePawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

/** Player's Game paddle which inherits the @Pawn object.
	Handles the movement of the paddle.
	Control is given to the first joining player(Player0) */

const float SpeedFactor = 1500.0f;

// Sets default values
APaddlePawn::APaddlePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set as controlled by first player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create static mesh and set its collision profile
	OurStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OurStaticMeshComponent->SetupAttachment(RootComponent);
	OurStaticMeshComponent->SetSimulatePhysics(true);
	OurStaticMeshComponent->SetCollisionProfileName(TEXT("Pawn"));
}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetForce();
}

// Sets paddle's force according to the @CurrentVelocity
void APaddlePawn::SetForce() 
{
	if (!CurrentVelocity.IsZero())
	{
		// Get the direction of our move input
		FVector Direction = CurrentVelocity * OurStaticMeshComponent->GetBodyInstance()->GetBodyMass() * 10;

		// DeltaTime is already applied on AddForce
		OurStaticMeshComponent->AddForce(Direction);
	}
}

// Called to bind functionality to input
void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &APaddlePawn::MoveX);
}

// Listener for the input
void APaddlePawn::MoveX(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * SpeedFactor;
}

