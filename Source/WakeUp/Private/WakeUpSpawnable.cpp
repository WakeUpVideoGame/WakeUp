// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "WakeUpSpawnable.h"



AWakeUpSpawnable::AWakeUpSpawnable(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWakeUpSpawnable::Tick(float DeltaSeconds)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += ConstRotationValue * DeltaSeconds;
	SetActorRotation(CurrentRotation);
}

