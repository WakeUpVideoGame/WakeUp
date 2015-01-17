// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PowerPickup.generated.h"

/**
 * 
 */
UCLASS()
class WAKEUP_API APowerPickup : public AActor
{
	GENERATED_UCLASS_BODY()

	/** True when the pickup is able to be picked up, false if something deactivates the pickup */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerPickup)
	bool bIsActive;

	/** Set the amount of power (lucidity or energy => brightness) gives to the player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerPickup)
	float PowerPickupLevel;

	/** Simple collision primitive to use as the root component. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PowerPickup)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	/** StaticMeshComponent to represent the pickup in the level */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = PowerPickup)
	TSubobjectPtr<UStaticMeshComponent> PowerPickupMesh;

	/** Function to call when the pickup is collected */
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();
};
