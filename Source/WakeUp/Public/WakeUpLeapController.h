// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "WakeUpLeapController.generated.h"

class AWakeUpCharacter;

/**
 * 
 */
UCLASS()
class WAKEUP_API AWakeUpLeapController : public APlayerController
{
	GENERATED_BODY()

	AWakeUpLeapController(const FObjectInitializer& ObjectInitializer);

	AWakeUpCharacter* MyCharacter;

	
	int Wait;
	bool LPLeft, LPRight, LPJump;

	void MoveRight(float value);
	void Jump();
	void Action();

	virtual void Tick(float DeltaTime);

	virtual void SetSpawn(APawn* InPawn);
};
