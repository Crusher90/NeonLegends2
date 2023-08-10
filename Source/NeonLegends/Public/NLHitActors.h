// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NLGameMode.h"
#include "BuffTypes.h"
#include "NLHitActors.generated.h"

UCLASS()
class NEONLEGENDS_API ANLHitActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANLHitActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USceneComponent> SceneComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> HitActorMesh;

	UPROPERTY()
	TObjectPtr<class ANLGameMode> GM;

protected:
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	UFUNCTION()
	virtual void OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:
	UPROPERTY()
	class ANLCharacter *Character;
};
