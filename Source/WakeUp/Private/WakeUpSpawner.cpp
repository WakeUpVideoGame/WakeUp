// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "WakeUpSpawner.h"
#include "WakeUpSpawnable.h"


AWakeUpSpawner::AWakeUpSpawner(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the simple StaticMeshComponent to represent the pickup in the level 
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));

	// Set the StaticMeshComponent as the root component
	RootComponent = WhereToSpawn;

	// Set the delay range and get the first SpawnDelay
	// minimum et maximum entre chaque spawn
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
	SpawnDelay = GetRandomSpawnDelay();

	// Make the SpawnVolume tickable
	PrimaryActorTick.bCanEverTick = true;
}



void AWakeUpSpawner::SpawnObject()
{
	// if we have set something to spawn
	UWorld* const World = GetWorld();
	if (WhatToSpawn != NULL)
	{
		// Check the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		//Get a random location to spawn at
		FVector SpawnLocation = GetRandomPointInVolume();

		// Get a random rotation for the spawned object
		FRotator SpawnRotation;
		SpawnRotation.Yaw = FMath::FRand() * 0.f;
		SpawnRotation.Pitch = 90.f;
		SpawnRotation.Roll = 90.f;

		// Spawn the pickup
		AWakeUpSpawnable* const SpawnedLog = World->SpawnActor<AWakeUpSpawnable>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	}
}

float AWakeUpSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

FVector AWakeUpSpawner::GetRandomPointInVolume()
{
	FVector RandomLocation;
	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;

	FVector Origin;
	FVector BoxExtent;

	// Get the SpawnVolume's origin and box extent
	Origin = WhereToSpawn->Bounds.Origin;
	BoxExtent = WhereToSpawn->Bounds.BoxExtent;

	// Calculate the minimum X, Y, and Z
	MinX = Origin.X - BoxExtent.X / 2.f;
	MinY = Origin.Y - BoxExtent.Y / 2.f;
	MinZ = Origin.Z - BoxExtent.Z / 2.f;

	// Calculate the maximum X, Y, and Z
	MaxX = Origin.X + BoxExtent.X / 2.f;
	MaxY = Origin.Y + BoxExtent.Y / 2.f;
	MaxZ = Origin.Z + BoxExtent.Z / 2.f;

	// The random spawn location will fall between the min and max X, Y, and Z
	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	// Return the random spawn location
	return RandomLocation;
}

void AWakeUpSpawner::Tick(float DeltaSeconds)
{
	// Always add delataTime to our Spawn Time
	SpawnTime += DeltaSeconds;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn)
	{
		SpawnObject();

		//Deduct spawn delay from accumulated time value
		SpawnTime -= SpawnDelay;

		SpawnDelay = GetRandomSpawnDelay();
	}
}