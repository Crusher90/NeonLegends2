// Fill out your copyright notice in the Description page of Project Settings.


#include "KillActorVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
AKillActorVolume::AKillActorVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	KillBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBox"));
	SetRootComponent(KillBox);
	KillBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	KillBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AKillActorVolume::BeginPlay()
{
	Super::BeginPlay();
	KillBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::DestroyActors);
}

// Called every frame
void AKillActorVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillActorVolume::DestroyActors(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) 
{
	if(!OtherActor)
		return;
	OtherActor->Destroy();
}


