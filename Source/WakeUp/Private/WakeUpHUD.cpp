// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "WakeUpHUD.h"
#include "WakeUpGameMode.h"
#include "WakeUpCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"

AWakeUpHUD::AWakeUpHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;
}

void AWakeUpHUD::DrawHUD()
{
	// Get the screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	// Call to the parent versions of DrawHUD
	Super::DrawHUD();

	// Get the character and print its power level
	AWakeUpCharacter* MyCharacter = Cast<AWakeUpCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	FString PowerLevelString = FString::Printf(TEXT("%10.1f"), FMath::Abs(MyCharacter->PowerLevel));
	/*DrawText(PowerLevelString, FColor::White, 50, 50, HUDFont);*/

	AWakeUpGameMode* MyGameMode = Cast<AWakeUpGameMode>(UGameplayStatics::GetGameMode(this));
	// if the game is over
	if (MyGameMode->GetCurrentState() == EWakeUpState::EGameOver)
	{
		// create a variable for storing the size of printing Game Over
		FVector2D GameOverSize;
		GetTextSize(TEXT("GAME OVER"), GameOverSize.X, GameOverSize.Y, HUDFont);
		DrawText(TEXT("GAME OVER"), FColor::White, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.Y - GameOverSize.Y) / 2.0f, HUDFont);
	}
}
