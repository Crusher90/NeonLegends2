// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NLAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API UNLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties", meta = (AllowPrivateAccess = "true"))
	class ANLCharacter *NLCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties", meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;
};
