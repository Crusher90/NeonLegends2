// Fill out your copyright notice in the Description page of Project Settings.

#include "NLHitActors.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANLHitActors::ANLHitActors()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	HitActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	HitActorMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ANLHitActors::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ANLGameMode>(UGameplayStatics::GetGameMode(this));
	HitActorMesh->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
	HitActorMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlap);
}

// Called every frame
void ANLHitActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANLHitActors::OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if (!OtherActor)
		return;
	Character = Cast<ANLCharacter>(OtherActor);
}

void ANLHitActors::OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!OtherActor)
		return;
	Character = Cast<ANLCharacter>(OtherActor);
}
