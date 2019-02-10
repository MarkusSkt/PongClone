// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreTriggerBox.h"
#include "Components/TextRenderComponent.h"
#include "Engine/TextRenderActor.h"

/** Score trigger that listens for overlapping ball
  and increases score accordingly. We can safely assume
  that no other object will be able to overlap this trigger
  so further checks have been left undone */


AScoreTriggerBox::AScoreTriggerBox()
{
	// Handle ball overlapping
	OnActorBeginOverlap.AddDynamic(this, &AScoreTriggerBox::OnOverlapBegin);
}

void AScoreTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AScoreTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		GiveScore();
	}
}

// Update score + text
void AScoreTriggerBox::GiveScore() 
{
	UE_LOG(LogTemp, Warning, TEXT("Give Score"));

	Score++;

	FString NewString = FString::FromInt(Score);
	ScoreText->GetTextRender()->SetText(NewString);
}

