// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ScoreTriggerBox.generated.h"

/**
 *
 */
UCLASS()
class PONGCLONE_API AScoreTriggerBox : public ATriggerBox
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

public:

	AScoreTriggerBox();

	UPROPERTY(EditAnywhere)
		class ATextRenderActor* ScoreText;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// Current score for the opposite player
	int Score;

	void GiveScore();
};
