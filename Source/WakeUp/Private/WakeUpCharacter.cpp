// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "WakeUp.h"
#include "WakeUpCharacter.h"
#include "JumpPowerPickup.h"
#include "WakeUpGameMode.h"
#include "Kismet/GameplayStatics.h"

AWakeUpCharacter::AWakeUpCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set a base power level for the character
	PowerLevel = 0;
	bIsJumpPowerActivated = false;

	// Create our power collection volume
	CollectionSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	
	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Face in the direction we are moving..
	CharacterMovement->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->GravityScale = 2.f;
	CharacterMovement->AirControl = 0.80f;
	CharacterMovement->JumpZVelocity = 1000.f;
	CharacterMovement->GroundFriction = 3.f;
	CharacterMovement->MaxWalkSpeed = 450.f;
	CharacterMovement->MaxFlySpeed = 600.f;

	CharacterMovement->bConstrainToPlane = true;
	CharacterMovement->SetPlaneConstraintNormal(FVector(-1.0f, 0.0f, 0.0f));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWakeUpCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &AWakeUpCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AWakeUpCharacter::StopJumping);

	InputComponent->BindAction("Action", IE_Released, this, &AWakeUpCharacter::Action);

	InputComponent->BindAxis("MoveRight", this, &AWakeUpCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &AWakeUpCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AWakeUpCharacter::TouchStopped);
}

void AWakeUpCharacter::Jump()
{
	if (bIsJumpPowerActivated == true)
	{
		ACharacter::Jump();
	}
}

void AWakeUpCharacter::StopJumping()
{
	if (bIsJumpPowerActivated == true)
	{
		ACharacter::StopJumping();
	}
}

void AWakeUpCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AWakeUpCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	if (bIsJumpPowerActivated == true)
	{
		Jump();
	}	
}

void AWakeUpCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (bIsJumpPowerActivated == true)
	{
		StopJumping();
	}
}

void AWakeUpCharacter::CollectPowers()
{
	float PowerPickupLevel = 0.f;

	//AWakeUpCharacterGameMode* MyGameMode = Cast<ATutorialCodeGameMode>(UGameplayStatics::GetGameMode(this));

	//if we are currently playing
	//if (MyGameMode->GetCurrentState() == EWakeUpPlayState::EPlaying)
	//{

		// Get all overlapping Actors and store them in a CollectedActors array
		TArray<AActor*> CollectedActors;
		CollectionSphere->GetOverlappingActors(CollectedActors);

		// For each Actor collected
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			// Cast the collected Actor to APowerPickup
			APowerPickup* const TestPower = Cast<APowerPickup>(CollectedActors[iCollected]);

			// if the cast is successful, and the power is valid and active 
			if (TestPower && !TestPower->IsPendingKill() && TestPower->bIsActive)
			{
				// Store its new power for adding to the character's power
				PowerPickupLevel = PowerPickupLevel + TestPower->PowerPickupLevel;
				// Call the power's OnPickedUp function
				TestPower->OnPickedUp();
				// Deactivate the power pickup
				TestPower->bIsActive = false;
			}
		}

		if (PowerPickupLevel > 0.f)
		{
			// Call the Blueprinted implementation of PowerUp with the total level power as input
			PowerUp(PowerPickupLevel);
		}
	//}
}

void AWakeUpCharacter::ActivatePower()
{
	if (PowerLevel >= 1000)
	{
		bIsJumpPowerActivated = true;
	}
}

void AWakeUpCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//CharacterMovement->MaxWalkSpeed = SpeedFactor * PowerLevel + BaseSpeed;
}