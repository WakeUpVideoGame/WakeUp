// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "WakeUpCharacter.generated.h"

UCLASS(config=Game)
class AWakeUpCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Collection Volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
	TSubobjectPtr<class USphereComponent> CollectionSphere;

	/** Power level (lucidity or energy => brightness) of the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
	float PowerLevel;

	virtual void Tick(float DeltaSeconds) OVERRIDE;

protected:

	/** Called when we press a key (P), to collect any power */
	UFUNCTION(BlueprintCallable, Category = Power)
	void CollectPowers();

	/** Called by CollectPowers() to use the Blueprinted PowerUp functionality */
	UFUNCTION(BlueprintImplementableEvent, Category = Power)
	void PowerUp(float PowerPickupLevel); //float PowerPickupLevel

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};