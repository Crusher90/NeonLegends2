// Fill out your copyright notice in the Description page of Project Settings.

#include "NLLoadingScreen.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "NLCharacter.h"

bool UNLLoadingScreen::Initialize()
{
    if (!Super::Initialize())
        return false;
    PlayAnimation(WA_LoadingAnimation);
    bIsPlaying = IsAnimationPlaying(WA_LoadingAnimation);
    FTimerHandle AnimationTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(AnimationTimerHandle, this, &ThisClass::OnAnimationStoppedPlaying, 6.f);
    return true;
}

void UNLLoadingScreen::OnAnimationStoppedPlaying()
{
    RemoveFromParent();
    ANLCharacter *NLCharacter = Cast<ANLCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (NLCharacter)
    {
        NLCharacter->SetCameraView();
        NLCharacter->CheckForLoadGame();
    }
}
