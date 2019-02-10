// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaddleActorAI.generated.h"

UCLASS()
class PONGCLONE_API APaddleActorAI : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APaddleActorAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveToBall();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* OurStaticMeshComponent;

	UPROPERTY(EditAnywhere)
		class ABallActor* Ball;

	FVector CurrentVelocity;
};
