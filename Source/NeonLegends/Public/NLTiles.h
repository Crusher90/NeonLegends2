// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NLTiles.generated.h"

UCLASS()
class NEONLEGENDS_API ANLTiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANLTiles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent *SceneComp;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UStaticMeshComponent *TileMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UStaticMeshComponent *BuildingComp;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UStaticMeshComponent *BuildingComp2;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UBoxComponent *TileBoxComp;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class ANLCharacter *MainCharacter;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UArrowComponent *ArrowComp;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UArrowComponent *ArrowComp1;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UStaticMeshComponent *BuildingSideMesh1;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UStaticMeshComponent *BuildingSideMesh2;

	UPROPERTY(VisibleAnywhere, Category = "TileProperties")
	class UParticleSystemComponent *AirParticles;

	FVector HitActorLocation;

	UPROPERTY()
	class ANLGameMode *GM;

public:
	FVector TileSpawnLocation;

protected:
	UFUNCTION()
	void OnTileBoxOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
