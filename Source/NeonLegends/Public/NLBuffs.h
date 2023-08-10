// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NLHitActors.h"
#include "BuffTypes.h"
#include "NLBuffs.generated.h"

/**
 *
 */

UCLASS()
class NEONLEGENDS_API ANLBuffs : public ANLHitActors
{
	GENERATED_BODY()

public:
	ANLBuffs();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class URotatingMovementComponent> RotMoveComp;

	UPROPERTY(EditAnywhere, Category = "BuffType")
	EPickupBuffType BuffType;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UTextRenderComponent> BuffName;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundCue> OverlapSound;

protected:
	virtual void OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
};
