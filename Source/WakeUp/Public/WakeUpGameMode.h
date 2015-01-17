// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "WakeUpGameMode.generated.h"

// enum to store the current state of gameplay
enum class EWakeUpPlayState : short //uint8
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class AWakeUpGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	EWakeUpPlayState GetCurrentState() const;

	void SetCurrentState(EWakeUpPlayState NewState);

	virtual void BeginPlay() OVERRIDE;

private:

	EWakeUpPlayState CurrentState;

	void HandleNewState(EWakeUpPlayState NewState);
};

FORCEINLINE EWakeUpPlayState AWakeUpGameMode::GetCurrentState() const
{
	return CurrentState;
}
