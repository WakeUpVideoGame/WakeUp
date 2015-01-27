// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WakeUpSpawnable.generated.h"

/**
 * 
 */
UCLASS()
class WAKEUP_API AWakeUpSpawnable : public AActor
{
	GENERATED_UCLASS_BODY()

protected:
	float const ConstRotationValue = 0.0f;

	virtual void Tick(float DeltaSeconds);
	
};
