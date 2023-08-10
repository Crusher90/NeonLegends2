// Fill out your copyright notice in the Description page of Project Settings.

#include "NLBuffs.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ANLBuffs::ANLBuffs()
{
    HitActorMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HitActorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HitActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    RotMoveComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotMoveComp"));

    BuffName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("BuffName"));
    BuffName->SetupAttachment(HitActorMesh);

    BuffType = EPickupBuffType::EPBT_Max;
}

void ANLBuffs::OnActorBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    Super::OnActorBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    if (Character)
    {
        if (GM)
        {
            GM->ActivateBuff(BuffType);
            UGameplayStatics::PlaySound2D(this, OverlapSound);
        }
        Destroy();
    }
}
