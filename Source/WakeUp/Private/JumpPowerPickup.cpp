// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "JumpPowerPickup.h"


AJumpPowerPickup::AJumpPowerPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// The base power level given to the character when he gets the jump power
	PowerPickupLevel = 1000;
}

void AJumpPowerPickup::OnPickedUp_Implementation()
{
	// No particular behavior for JumpPowerPickup when it is picked up
	Super::OnPickedUp_Implementation();
	Destroy();
}
