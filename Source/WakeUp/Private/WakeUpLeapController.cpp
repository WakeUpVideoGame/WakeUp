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
		Device->getLeapController().enableGesture(Leap::Gesture::TYPE_CIRCLE);

		Device->getLeapController().config().setFloat("Gesture.Swipe.MinLength", 130.0);
		Device->getLeapController().config().setFloat("Gesture.Swipe.MinVelocity", 5);

		Device->getLeapController().config().setFloat("Gesture.Circle.MinRadius", 100.0);
		Device->getLeapController().config().setFloat("Gesture.Circle.MinArc", 6.);

		Device->getLeapController().config().save();
	}
}

void AWakeUpLeapController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyCharacter = Cast<AWakeUpCharacter>(GetPawn());

	FLeapMotionDevice* Device = FLeapMotionControllerPlugin::GetLeapDeviceSafe();

	if (Wait <= 0)
	{
		Wait = 0;
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

					if (gest.type() == Leap::Gesture::TYPE_CIRCLE){
						Leap::CircleGesture circleGesture = Leap::CircleGesture(gest);
						Action();
					}

					if (gest.type() == Leap::Gesture::TYPE_SWIPE) {
						Leap::SwipeGesture swipeGesture = Leap::SwipeGesture(gest);

						// Classify swipe as either horizontal or vertical
						auto isHorizontal = abs(swipeGesture.direction().x) > abs(swipeGesture.direction().y);
						// Classify as right-left or up-down
						if (isHorizontal){
							if (swipeGesture.direction().x > 0){
								/*GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Cyan, FString(TEXT("Right")));*/
								LPLeft = false;
								LPRight = true;
								auto speed = (swipeGesture.speed() * swipeGesture.speed()) / 50;
								MyCharacter->CharacterMovement->MaxWalkSpeed = (speed > 450) ? 450 : speed;
							}
							else {
								/*GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Yellow, FString(TEXT("Left")));*/
								LPRight = false;
								LPLeft = true;
								auto speed = (swipeGesture.speed() * swipeGesture.speed()) / 50;
								MyCharacter->CharacterMovement->MaxWalkSpeed = (speed > 450) ? 450 : speed;
							}
						}
						else { //vertical
							if (swipeGesture.direction().y > 0){
								/*GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Black, FString(TEXT("Up")));*/
								if (swipeGesture.direction().x > 0)
									MoveRight(175.f);
								else
									MoveRight(-175.f);
								Jump();
								LPRight = false;
								LPLeft = false;
							}
							else {
								/*GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::White, FString(TEXT("Down")));*/
								LPLeft = false;
								LPRight = false;
								LPJump = false;
								Action();
								Wait = 45;
							}
						}
					}
				}
			}
		}
		else{
			/*GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString(TEXT("LeapController - No Data")));*/
		}
	}
	else
	{
		--Wait;
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
	if (MyCharacter != NULL)
		MyCharacter->Action();
}
