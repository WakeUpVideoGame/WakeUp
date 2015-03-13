// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "WakeUpRotation.h"


AWakeUpRotation::AWakeUpRotation(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWakeUpRotation::Tick(float DeltaSeconds)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Roll += ConstRotationValue * DeltaSeconds;
	SetActorRotation(CurrentRotation);
}