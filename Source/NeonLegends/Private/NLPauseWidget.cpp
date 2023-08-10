// Fill out your copyright notice in the Description page of Project Settings.


#include "NLPauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UNLPauseWidget::Initialize()
{
    if(!Super::Initialize())
        return false;

    if(BT_Resume)
    {
        BT_Resume->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Resume);
    }
    if(BT_MainMenu)
    {
        BT_MainMenu->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_MainMenu);
    }
    return true;
}

void UNLPauseWidget::ClickedBT_Resume()
{
    UGameplayStatics::SetGamePaused(this, 0);
    SetVisibility(ESlateVisibility::Hidden);
}

void UNLPauseWidget::ClickedBT_MainMenu()
{
    GetWorld()->GetTimerManager().ClearTimer(GM->ScoreTimerHandle);
    GM->Coins += GM->RunnerCoins;
    GM->SaveGame();
    UGameplayStatics::OpenLevel(this, FName("Map1"));
}
