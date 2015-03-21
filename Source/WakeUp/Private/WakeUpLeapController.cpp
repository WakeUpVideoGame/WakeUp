// Fill out your copyright notice in the Description page of Project Settings.

#include "WakeUp.h"
#include "WakeUpLeapController.h"

#include "WakeUpCharacter.h"

#include "Engine.h"

#include "LeapMotionControllerPlugin.h"
#include "LeapMotionDevice.h"
#include "Leap.h"
#include "LeapMotionTypes.h"
#include "LeapMotionDevice.h"

AWakeUpLeapController::AWakeUpLeapController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	FLeapMotionDevice* Device = FLeapMotionControllerPlugin::GetLeapDeviceSafe();

	if (Device && Device->IsConnected())
	{
		// Enable some gestures
		Device->getLeapController().enableGesture(Leap::Gesture::TYPE_SWIPE);

		Device->getLeapController().config().setFloat("Gesture.Swipe.MinLength", 100.0);
		Device->getLeapController().config().setFloat("Gesture.Swipe.MinVelocity", 50);
		Device->getLeapController().config().save();
	}
}

void AWakeUpLeapController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyCharacter = Cast<AWakeUpCharacter>(GetPawn());

	FLeapMotionDevice* Device = FLeapMotionControllerPlugin::GetLeapDeviceSafe();

	if (Wait > 0) --Wait;

	if (Device && Device->IsConnected())
	{
		Device->SetReferenceFrameOncePerTick();
		Leap::Frame frame = Device->Frame();

// 		for (Leap::Hand hand : frame.hands())
// 		{
// 			for (Leap::Finger finger : hand.fingers()){
// 				FString fingerLabel = FString::Printf(TEXT("        Finger %u: "), finger.id());
// 				fingerLabel += finger.tipPosition().toString().c_str();
// 				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, fingerLabel);
// 			}
// 
// 			FString handLabel = FString::Printf(TEXT("    Hand %u: "), hand.id());
// 			handLabel += hand.palmPosition().toString().c_str();
// 			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, handLabel);
// 		}

// 		FString leapLabel = FString::Printf(TEXT("LeapController - Frame: %u"), frame.id());
// 		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, leapLabel);

		// Handle gesture
		if (frame.isValid() && frame.gestures().count() > 0) {
			for (Leap::Gesture gest : frame.gestures()) {
				Leap::SwipeGesture swipeGesture = Leap::Gesture::invalid();
				if (gest.type() == Leap::Gesture::TYPE_SWIPE) {
					swipeGesture = Leap::SwipeGesture(gest);

					GEngine->AddOnScreenDebugMessage(-1, 1000000.f, FColor::Cyan, FString(TEXT("It's a swipe")));

					// Classify swipe as either horizontal or vertical
					auto isHorizontal = abs(swipeGesture.direction().x) > abs(swipeGesture.direction().y);
					// Classify as right-left or up-down
					if (isHorizontal){
						if (swipeGesture.direction().x > 0){
							GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Cyan, FString(TEXT("Right")));
							if (LPLeft)
							{
								LPLeft = false;
							}
							else
							{
								LPRight = true;
							}
						}
						else {
							GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Yellow, FString(TEXT("Left")));
							if (LPRight)
							{
								LPRight = false;
							}
							else
							{
								LPLeft = true;
							}
						}
					}
					else { //vertical
						if (swipeGesture.direction().y > 0){
							GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Black, FString(TEXT("Up")));
							Jump();
						}
						else {
							GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::White, FString(TEXT("Down")));
						}
					}
				}
			}
		}
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString(TEXT("LeapController - No Data")));
		/*UE_LOG(Controller, Warning, TEXT("WakeUpLeapController::LeapController - No Data"));*/
	}

	if (LPLeft) MoveRight(-1.f);
	if (LPRight) MoveRight(1.f);
}

void AWakeUpLeapController::SetSpawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	//Setting MyCharacter to the adress of InPawn if InPawn is a AWakeUpCharacter
	APawn* Pawn = GetPawn();
	MyCharacter = (Pawn ? Cast<AWakeUpCharacter>(Pawn) : NULL);
}

void AWakeUpLeapController::MoveRight(float value)
{
	if (MyCharacter != NULL)
		MyCharacter->MoveRight(value);
}

void AWakeUpLeapController::Jump()
{
	if (MyCharacter != NULL)
		MyCharacter->Jump();
}

void AWakeUpLeapController::Action()
{

}
