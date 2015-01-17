// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "JumpPowerPickup.h"


AJumpPowerPickup::AJumpPowerPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// The base power level given to the character when he gets the jump power
	PowerPickupLevel = 150.f;
}

void AJumpPowerPickup::OnPickedUp_Implementation()
{
	// Call the parent implementation of OnPickedUp first.
	Super::OnPickedUp_Implementation();
	// Destroy the power pickup
	Destroy();
}
