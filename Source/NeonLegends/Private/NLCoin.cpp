// Fill out your copyright notice in the Description page of Project Settings.

#include "NLCoin.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NLPlayerController.h"
#include "Sound/SoundCue.h"

ANLCoin::ANLCoin()
{
    PrimaryActorTick.bCanEverTick = true;

    HitActorMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HitActorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HitActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    HitActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

    RotMoveComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMoveComp"));
}

void ANLCoin::OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    Super::OnActorBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    if (Character && GM)
    {
        if (!GM->CoinMagnetBuffTimer.IsValid())
        {
            Destroy();
        }
        else
        {
            SetLifeSpan(0.1f);
        }
        GM->RunnerCoins += (1 * GM->CoinsMultiplier);
        Character->GetNLPlayerController()->SetHUDCoins(GM->RunnerCoins);
        UGameplayStatics::PlaySound2D(this, OverlapSound);
    }
}  


