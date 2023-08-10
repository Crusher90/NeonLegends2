// Fill out your copyright notice in the Description page of Project Settings.

#include "NLIntroWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "NLHUD.h"
#include "NLCharacter.h"
#include "NLCharacterWidget.h"
#include "NLPowerupWidget.h"
#include "NLInfoOverlay.h"
#include "NLSettingsWidget.h"

bool UNLIntroWidget::Initialize()
{
    if (!Super::Initialize())
        return false;

    if (BT_CharacterChange)
    {
        BT_CharacterChange->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_CharacterChange);
    }
    if (BT_Play)
    {
        BT_Play->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Play);
    }
    if (BT_Powerups)
    {
        BT_Powerups->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Powerups);
    }
    if (BT_Settings)
    {
        BT_Settings->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Settings);
    }
    if (TB_Coins)
    {
        TB_Coins->SetText(FText::AsNumber(GM->Coins));
    }
    return true;
}

void UNLIntroWidget::ClickedBT_CharacterChange()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->CharacterWidget)
    {
        PC->NLHUD->CharacterWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetCharacterWidgetCoins(GM->Coins);
    }
}

void UNLIntroWidget::ClickedBT_Play()
{
    ANLCharacter *Character = Cast<ANLCharacter>(GetOwningPlayer()->GetCharacter());
    if (Character)
    {
        Character->SetIsInputEnabled(true);
        GetOwningPlayer()->SetViewTargetWithBlend(Character, 5.f, EViewTargetBlendFunction::VTBlend_Cubic);
    }
    if (PC->NLHUD && PC->NLHUD->PowerupWidget)
    {
        PC->NLHUD->PowerupWidget->RemoveFromParent();
        PC->NLHUD->CharacterWidget->RemoveFromParent();
    }
    RemoveFromParent();
    if (PC->NLHUD && PC->NLHUD->InfoOverlay)
    {
        PC->NLHUD->InfoOverlay->SetVisibility(ESlateVisibility::Visible);
        GetWorld()->GetTimerManager().UnPauseTimer(PC->NLHUD->InfoOverlay->DisableHeadStartTimer);
        GM->SetScoreTimer();
    }
}

void UNLIntroWidget::ClickedBT_Powerups()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->PowerupWidget)
    {
        PC->NLHUD->PowerupWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetPowerupWidgetCoins(GM->Coins);
    }
}

void UNLIntroWidget::ClickedBT_Settings()
{
    if (SettingsWidget)
    {
        if (SettingsWidget->GetVisibility() == ESlateVisibility::Visible)
        {
            SettingsWidget->SetVisibility(ESlateVisibility::Hidden);
            BT_Play->SetIsEnabled(true);
            BT_Powerups->SetIsEnabled(true);
            BT_CharacterChange->SetIsEnabled(true);
        }
        else
        {
            SettingsWidget->SetVisibility(ESlateVisibility::Visible);
            BT_Play->SetIsEnabled(false);
            BT_Powerups->SetIsEnabled(false);
            BT_CharacterChange->SetIsEnabled(false);
        }
    }
}
