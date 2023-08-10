// Fill out your copyright notice in the Description page of Project Settings.

#include "NLTiles.h"
#include "Components/BoxComponent.h"
#include "NLCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NLGameMode.h"
#include "NLHitActors.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ANLTiles::ANLTiles()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	TileMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMeshComp"));
	TileMeshComp->SetupAttachment(GetRootComponent());

	BuildingComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingComp"));
	BuildingComp->SetupAttachment(GetRootComponent());

	BuildingComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingComp2"));
	BuildingComp2->SetupAttachment(GetRootComponent());

	TileBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("TileBoxComp"));
	TileBoxComp->SetupAttachment(GetRootComponent());
	TileBoxComp->SetBoxExtent(FVector(50.f, 500.f, 500.f));

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("TileSpawn"));
	ArrowComp->SetupAttachment(GetRootComponent());

	ArrowComp1 = CreateDefaultSubobject<UArrowComponent>(TEXT("HitActorSpawn"));
	ArrowComp1->SetupAttachment(GetRootComponent());

	BuildingSideMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingSideMesh1"));
	BuildingSideMesh1->SetupAttachment(BuildingComp);

	BuildingSideMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingSideMesh2"));
	BuildingSideMesh2->SetupAttachment(BuildingComp2);

	AirParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AirParticles"));
	AirParticles->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ANLTiles::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ANLGameMode>(UGameplayStatics::GetGameMode(this));
	if (!GM)
		return;

	TileSpawnLocation = ArrowComp->GetComponentLocation();
	HitActorLocation = ArrowComp1->GetComponentLocation();
	GM->SpawnHitActors(HitActorLocation);
	TileBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTileBoxOverlapBegin);
}

// Called every frame
void ANLTiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANLTiles::OnTileBoxOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!OtherActor)
		return;
	MainCharacter = MainCharacter == nullptr ? Cast<ANLCharacter>(OtherActor) : MainCharacter;
	if (MainCharacter)
	{
		if (GM)
		{
			GM->SpawnTiles(GM->SpawnedTile->TileSpawnLocation);
			if(MainCharacter->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying)
				return;
			GM->LegendSpeed += GM->LegendSpeedMultiplier;
		}
		MainCharacter->GetCharacterMovement()->MaxWalkSpeed = GM->LegendSpeed;
		MainCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = GM->LegendSpeed;
		MainCharacter->GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(MainCharacter->GetCharacterMovement()->MaxWalkSpeed, 0.f, 2000.f);
		MainCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched = FMath::Clamp(MainCharacter->GetCharacterMovement()->MaxWalkSpeedCrouched, 0.f, 2000.f);
	}
}
