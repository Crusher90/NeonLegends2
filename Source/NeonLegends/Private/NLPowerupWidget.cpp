// Fill out your copyright notice in the Description page of Project Settings.

#include "NLPowerupWidget.h"
#include "Components/Button.h"
#include "NLHUD.h"
#include "NLIntroWidget.h"
#include "NLCharacterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

bool UNLPowerupWidget::Initialize()
{
    if (!Super::Initialize())
        return false;

    PC->SetPowerupWidgetCoins(GM->Coins);
    if (BT_Back)
    {
        BT_Back->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Back);
    }
    if (BT_Characters)
    {
        BT_Characters->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Characters);
    }
    if (BT_HighJumpUpgrade)
    {
        BT_HighJumpUpgrade->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_HighJumpUpgrade);
    }
    if (BT_ScoreUpgrade)
    {
        BT_ScoreUpgrade->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_ScoreUpgrade);
    }
    if (BT_CoinsUpgrade)
    {
        BT_CoinsUpgrade->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_CoinsUpgrade);
    }
    if (BT_CoinMagnetUpgrade)
    {
        BT_CoinMagnetUpgrade->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_CoinMagnetUpgrade);
    }
    if (BT_HeadStartUpgrade)
    {
        BT_HeadStartUpgrade->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_HeadStartUpgrade);
    }
    return true;
}

void UNLPowerupWidget::ClickedBT_Back()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->IntroWidget)
    {
        PC->NLHUD->IntroWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetIntroCoins(GM->Coins);
    }
}

void UNLPowerupWidget::ClickedBT_Characters()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->CharacterWidget)
    {
        PC->NLHUD->CharacterWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetCharacterWidgetCoins(GM->Coins);
    }
}

void UNLPowerupWidget::ClickedBT_HighJumpUpgrade()
{
    ClickedBT_Upgrade(GM->HighJumpUpgradeThreshold, GM->HighJumpUpgradePercent, PB_HighJumpUpgrade, TB_HighJumpValue, GM->JumpBuffTime);
}

void UNLPowerupWidget::ClickedBT_ScoreUpgrade()
{
    ClickedBT_Upgrade(GM->ScoreUpgradeThreshold, GM->ScoreUpgradePercent, PB_ScoreUpgrade, TB_ScoreValue, GM->ScoreMultiplierBuffTime);
}

void UNLPowerupWidget::ClickedBT_CoinsUpgrade()
{
    ClickedBT_Upgrade(GM->CoinsUpgradeThreshold, GM->CoinsUpgradePercent, PB_CoinsUpgrade, TB_CoinsValue, GM->CoinMultiplierBuffTime);
}

void UNLPowerupWidget::ClickedBT_CoinMagnetUpgrade()
{
    ClickedBT_Upgrade(GM->CoinMagnetUpgradeThreshold, GM->CoinMagnetUpgradePercent, PB_CoinMagnetUpgrade, TB_CoinMagnetValue, GM->CoinMagnetBuffTime);
}

void UNLPowerupWidget::ClickedBT_HeadStartUpgrade()
{
    ClickedBT_Upgrade(GM->HeadStartUpgradeThreshold, GM->HeadStartUpgradePercent, PB_HeadStartUpgrade, TB_HeadStartValue, GM->SpeedBuffTime);
}

void UNLPowerupWidget::ClickedBT_Upgrade(int32 &Threshold, float &Percent, UProgressBar *Bar, UTextBlock *Block, float &BuffTime)
{
    if (GM->Coins >= Threshold)
    {
        GM->Coins -= Threshold;
        PC->SetPowerupWidgetCoins(GM->Coins);
        Threshold = 2 * Threshold;
        Percent = Bar->GetPercent() + 0.2f;
        Bar->SetPercent(Percent);
        FString Value = FString::Printf(TEXT("₹ %d"), Threshold);
        Block->SetText(FText::FromString(Value));
        BuffTime += 5.f;
        GM->SaveGame();
    }
}