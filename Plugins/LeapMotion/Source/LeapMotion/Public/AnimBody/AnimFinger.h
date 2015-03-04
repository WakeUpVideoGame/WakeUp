#pragma once

#include "AnimBone.h"
#include "AnimFinger.generated.h"

UCLASS(BlueprintType)
class UAnimFinger : public UObject
{
	GENERATED_UCLASS_BODY()

	//Not used in basic animation
	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	TSubobjectPtr<UAnimBone> Metacarpal;

	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	TSubobjectPtr<UAnimBone> Proximal;

	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	TSubobjectPtr<UAnimBone> Intermediate;

	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	TSubobjectPtr<UAnimBone> Distal;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Finger")
	float Alpha;


	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	bool Enabled();

	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetEnabled(bool enable = true);

	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void TranslateFinger(FVector shift);

	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors = true);

	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetFromLeapFinger(class ULeapFinger* finger);
};