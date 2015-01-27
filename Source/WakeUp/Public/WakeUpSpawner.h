// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WakeUpSpawner.generated.h"

/**
 * 
 */

UCLASS()
class WAKEUP_API AWakeUpSpawner : public AActor
{
	GENERATED_UCLASS_BODY()

		/** BoxComponent to specify the spawning area within the level */
		UPROPERTY(VisibleInstanceOnly, Category = Spawning)
		TSubobjectPtr<UBoxComponent> WhereToSpawn;

	/** The pickup to spawn */
	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class AWakeUpSpawnable> WhatToSpawn;

	/** Minimum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow;

	/** Maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh;

	/** Finds a random point within the BoxComponent */
	UFUNCTION(BlueprintPure, Category = Spawning)
		FVector GetRandomPointInVolume();

	virtual void Tick(float DeltaSeconds) OVERRIDE;




private:

	/** Calculate a random spawn delay */
	float GetRandomSpawnDelay();

	/** The current spawn delay */
	float SpawnDelay;

	/** Handles the spawning of a new object */
	void SpawnObject();

	/** The timer for when to spawn the object */
	float SpawnTime;
	
};
