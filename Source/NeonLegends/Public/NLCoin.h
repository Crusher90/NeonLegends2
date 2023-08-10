// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NLHitActors.h"
#include "NLCoin.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API ANLCoin : public ANLHitActors
{
	GENERATED_BODY()

public:
	ANLCoin();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class URotatingMovementComponent> RotMoveComp;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundCue> OverlapSound;

protected:
	virtual void OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
};
