// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "WakeUpGameMode.generated.h"

// enum to store the current state of gameplay
enum class EWakeUpState : short //uint8
{
	EPlaying,
	EGameOver,
	EPaused,
	EMenu,
	EConfiguration,
	ECinematic,
	ELeaderboard,
	EUnknown
};

UCLASS(minimalapi)
class AWakeUpGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	float DecayRate;

	EWakeUpState GetCurrentState() const;

	void SetCurrentState(EWakeUpState NewState);

	virtual void BeginPlay() override;

private:

	EWakeUpState CurrentState;

	void HandleNewState(EWakeUpState NewState);
};

FORCEINLINE EWakeUpState AWakeUpGameMode::GetCurrentState() const
{
	return CurrentState;
}
