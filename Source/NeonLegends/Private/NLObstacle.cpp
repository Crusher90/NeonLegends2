// Fill out your copyright notice in the Description page of Project Settings.

#include "NLObstacle.h"
#include "NLPlayerController.h"
#include "NLHUD.h"
#include "NLDeadScreenWidget.h"
#include "Components/TextBlock.h"
#include "Components/CapsuleComponent.h"

ANLObstacle::ANLObstacle()
{
    HitActorMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HitActorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    HitActorMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ANLObstacle::OnActorHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
    if (Character)
    {
        Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Character->GetMesh()->SetCollisionProfileName(FName("Ragdoll"), true);
        Character->GetMesh()->SetSimulatePhysics(true);
        GM->Coins += GM->RunnerCoins;
        GM->PC->NLHUD->DeadWidget->GetScoreText()->SetText(FText::AsNumber(GM->Score));
        GM->PC->NLHUD->DeadWidget->GetRunnerCoinsText()->SetText(FText::AsNumber(GM->RunnerCoins));
        GM->PC->NLHUD->DeadWidget->AddToViewport();
        GetWorldTimerManager().ClearTimer(GM->ScoreTimerHandle);
    }
}
