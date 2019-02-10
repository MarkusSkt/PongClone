// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddlePawn.generated.h"

UCLASS()
class PONGCLONE_API APaddlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector CurrentVelocity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OurStaticMeshComponent;

	void MoveX(float Value);
	void SetForce();
};
