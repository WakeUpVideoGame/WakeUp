// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "WakeUp.h"
#include "WakeUpGameMode.h"
#include "WakeUpCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "WakeUpHUD.h"

AWakeUpGameMode::AWakeUpGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set the default HUD class
	HUDClass = AWakeUpHUD::StaticClass();
}

void AWakeUpGameMode::Tick(float DeltaSeconds)
{
	AWakeUpCharacter* MyCharacter = Cast<AWakeUpCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	// if the character still has power
	if (MyCharacter->PowerLevel > 0.05)
	{
		// you can play
	}
	else
	{
		SetCurrentState(EWakeUpPlayState::EGameOver);
	}
}

void AWakeUpGameMode::SetCurrentState(EWakeUpPlayState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AWakeUpGameMode::HandleNewState(EWakeUpPlayState NewState)
{
	switch (NewState)
	{
		// When we're playing
		case EWakeUpPlayState::EPlaying:
			break;

		// if the game is over
		case EWakeUpPlayState::EGameOver:
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			PlayerController->SetCinematicMode(true, true, true);
		}
		break;

		case EWakeUpPlayState::EUnknown:
		default:
			// do nothing
			break;
	}
}

void AWakeUpGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EWakeUpPlayState::EPlaying);
}