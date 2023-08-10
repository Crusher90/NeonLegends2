// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NLHitActors.h"
#include "NLObstacle.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API ANLObstacle : public ANLHitActors
{
	GENERATED_BODY()

public:
	ANLObstacle();

protected:
	virtual void OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) override;
	
};
