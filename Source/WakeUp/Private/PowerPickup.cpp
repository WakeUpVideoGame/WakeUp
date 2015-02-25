// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "PowerPickup.h"


APowerPickup::APowerPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// The pickup is valid when it is created
	bIsActive = true;

	// Create the root SphereComponent to handle the pickup's collision
	BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	// Set the SphereComponent as the root component
	RootComponent = BaseCollisionComponent;

	// Create the static mesh component 
	PowerPickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PowerPickupMesh"));

	// Turn physics on for the static mesh
	PowerPickupMesh->SetSimulatePhysics(true);

	// Attach the StaticMeshComponent to the root component
	PowerPickupMesh->AttachTo(RootComponent);
}

void APowerPickup::OnPickedUp_Implementation()
{
	// Default behavior
	// Call the parent implementation of OnPickedUp first.
	//Super::OnPickedUp_Implementation();
	// Destroy the power pickup
	//Destroy();
}
