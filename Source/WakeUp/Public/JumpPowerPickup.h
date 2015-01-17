// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerPickup.h"
#include "JumpPowerPickup.generated.h"

/**
 * 
 */
UCLASS()
class WAKEUP_API AJumpPowerPickup : public APowerPickup
{
	GENERATED_UCLASS_BODY()

	/** Set the amount of power (lucidity or energy => brightness) gives to the player */
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
	// float PowerPickupLevel;

	/** Override the OnPickedUp function (use Implementation because this is a BlueprintNativeEvent) */
	void OnPickedUp_Implementation() override;
};
