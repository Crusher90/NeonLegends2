// Fill out your copyright notice in the Description page of Project Settings.

#include "NLInfoOverlay.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "NLPauseWidget.h"
#include "Components/TextBlock.h"

bool UNLInfoOverlay::Initialize()
{
    if (!Super::Initialize())
        return false;
        
    if (BT_Pause)
    {
        BT_Pause->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Pause);
    }
    if (BT_HeadStart)
    {
        BT_HeadStart->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_HeadStart);
    }
    if(PauseWidget)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    GetWorld()->GetTimerManager().SetTimer(DisableHeadStartTimer, this, &ThisClass::DisableHeadStartButton, 8.f);
    GetWorld()->GetTimerManager().PauseTimer(DisableHeadStartTimer);
    return true;
}

void UNLInfoOverlay::ClickedBT_Pause()
{
    UGameplayStatics::SetGamePaused(this, 1);
    if (PauseWidget)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Visible);
        PauseWidget->GetScoreText()->SetText(FText::AsNumber(GM->Score));
        PauseWidget->GetRunnerCoinsText()->SetText(FText::AsNumber(GM->RunnerCoins));
    }
}

void UNLInfoOverlay::ClickedBT_HeadStart()
{
    GM->ActivateBuff(EPickupBuffType::EPBT_Speed);
    DisableHeadStartButton();
}

void UNLInfoOverlay::DisableHeadStartButton()
{
    if (BT_HeadStart)
    {
        BT_HeadStart->SetIsEnabled(false);
        BT_HeadStart->SetVisibility(ESlateVisibility::Hidden);
    }
}
