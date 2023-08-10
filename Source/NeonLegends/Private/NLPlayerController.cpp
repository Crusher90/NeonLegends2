// Fill out your copyright notice in the Description page of Project Settings.


#include "NLPlayerController.h"
#include "NLHUD.h"
#include "NLInfoOverlay.h"
#include "NLIntroWidget.h"
#include "NLPowerupWidget.h"
#include "NLCharacterWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"



ANLPlayerController::ANLPlayerController()
{
    NLHUD = Cast<ANLHUD>(GetHUD());
}

void ANLPlayerController::BeginPlay()
{
    Super::BeginPlay();
    NLHUD = Cast<ANLHUD>(GetHUD());
}

void ANLPlayerController::SetHUDScore(int32 Score)
{
    bool IsHudValid = NLHUD && NLHUD->InfoOverlay;
    if (IsHudValid)
    {
        NLHUD->InfoOverlay->GetScoreText()->SetText(FText::AsNumber(Score));
    }
}

void ANLPlayerController::SetHUDCoins(int32 Coins)
{
    bool IsHudValid = NLHUD && NLHUD->InfoOverlay;
    if (IsHudValid)
    {
        NLHUD->InfoOverlay->GetCoinsText()->SetText(FText::AsNumber(Coins));
    }
}

void ANLPlayerController::SetIntroCoins(int32 Coins)
{
    bool IsHudValid = NLHUD && NLHUD->IntroWidget;
    if (IsHudValid)
    {
        NLHUD->IntroWidget->GetCoinsText()->SetText(FText::AsNumber(Coins));
    }
}

void ANLPlayerController::SetCharacterWidgetCoins(int32 Coins)
{
    bool IsHudValid = NLHUD && NLHUD->CharacterWidget;
    if (IsHudValid)
    {
        NLHUD->CharacterWidget->GetCoinsText()->SetText(FText::AsNumber(Coins));
    }
}

void ANLPlayerController::SetPowerupWidgetCoins(int32 Coins)
{
    bool IsHudValid = NLHUD && NLHUD->PowerupWidget;
    if (IsHudValid)
    {
        NLHUD->PowerupWidget->GetCoinsText()->SetText(FText::AsNumber(Coins));
    }
}

void ANLPlayerController::SetCharacterWidgetStatusValue(FText Value) 
{
    bool IsHudValid = NLHUD && NLHUD->CharacterWidget;
    if (IsHudValid)
    {
        NLHUD->CharacterWidget->GetStatusText()->SetText(Value);
    }
}

void ANLPlayerController::SetThresholdValuesAfterLoad(float CoinMagnetValue, float CoinsValue, float HeadStartValue, float HighJumpValue, float ScoreValue) 
{
    if(!NLHUD)
        return;
    NLHUD->PowerupWidget->TB_CoinMagnetValue->SetText(FText::AsNumber(CoinMagnetValue));
    NLHUD->PowerupWidget->TB_CoinsValue->SetText(FText::AsNumber(CoinsValue));
    NLHUD->PowerupWidget->TB_HeadStartValue->SetText(FText::AsNumber(HeadStartValue));
    NLHUD->PowerupWidget->TB_HighJumpValue->SetText(FText::AsNumber(HighJumpValue));
    NLHUD->PowerupWidget->TB_ScoreValue->SetText(FText::AsNumber(ScoreValue));
}

void ANLPlayerController::SetProgressBarValuesAfterLoad(float CoinMagnetUpgrade, float CoinsUpgrade, float HeadStartUpgrade, float HighJumpUpgrade, float ScoreUpgrade)
{
    if (!NLHUD)
        return;
    NLHUD->PowerupWidget->PB_CoinMagnetUpgrade->SetPercent(CoinMagnetUpgrade);
    NLHUD->PowerupWidget->PB_CoinsUpgrade->SetPercent(CoinsUpgrade);
    NLHUD->PowerupWidget->PB_HeadStartUpgrade->SetPercent(HeadStartUpgrade);
    NLHUD->PowerupWidget->PB_HighJumpUpgrade->SetPercent(HighJumpUpgrade);
    NLHUD->PowerupWidget->PB_ScoreUpgrade->SetPercent(ScoreUpgrade);
}
