// Fill out your copyright notice in the Description page of Project Settings.

#include "NLCharacterWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "NLCharacter.h"
#include "NLHUD.h"
#include "NLIntroWidget.h"
#include "NLPowerupWidget.h"

bool UNLCharacterWidget::Initialize()
{
    if (!Super::Initialize())
        return false;

    PC->SetCharacterWidgetCoins(GM->Coins);

    if (BT_Michelle)
    {
        BT_Michelle->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Michelle);
    }
    if (BT_Amy)
    {
        BT_Amy->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Amy);
    }
    if (BT_Eve)
    {
        BT_Eve->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Eve);
    }
    if (BT_Jackie)
    {
        BT_Jackie->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Jackie);
    }
    if (BT_James)
    {
        BT_James->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_James);
    }
    if (BT_Joe)
    {
        BT_Joe->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Joe);
    }
    if (BT_Kachujin)
    {
        BT_Kachujin->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Kachujin);
    }
    if (BT_Shannon)
    {
        BT_Shannon->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Shannon);
    }
    if (BT_Back)
    {
        BT_Back->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Back);
    }
    if (BT_Powerups)
    {
        BT_Powerups->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_Powerups);
    }
    return true;
}

void UNLCharacterWidget::ClickedBT_Amy()
{
    SetCharacterInGame(FName("Amy"), FString("200"));
}

void UNLCharacterWidget::ClickedBT_Michelle()
{
    SetCharacterInGame(FName("Michelle"), FString("0"));
}

void UNLCharacterWidget::ClickedBT_Eve()
{
    SetCharacterInGame(FName("Eve"), FString("300"));
}

void UNLCharacterWidget::ClickedBT_Jackie()
{
    SetCharacterInGame(FName("Jackie"), FString("500"));
}

void UNLCharacterWidget::ClickedBT_James()
{
    SetCharacterInGame(FName("James"), FString("800"));
}

void UNLCharacterWidget::ClickedBT_Joe()
{
    SetCharacterInGame(FName("Joe"), FString("1200"));
}

void UNLCharacterWidget::ClickedBT_Kachujin()
{
    SetCharacterInGame(FName("Kachujin"), FString("3500"));
}

void UNLCharacterWidget::ClickedBT_Shannon()
{
    SetCharacterInGame(FName("Shannon"), FString("4500"));
}

void UNLCharacterWidget::ClickedBT_Back()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->IntroWidget)
    {
        PC->NLHUD->IntroWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetIntroCoins(GM->Coins);
    }
}

void UNLCharacterWidget::ClickedBT_Powerups()
{
    SetVisibility(ESlateVisibility::Hidden);
    if (PC->NLHUD && PC->NLHUD->PowerupWidget)
    {
        PC->NLHUD->PowerupWidget->SetVisibility(ESlateVisibility::Visible);
        PC->SetPowerupWidgetCoins(GM->Coins);
    }
}

void UNLCharacterWidget::SetCharacterInGame(FName NameOfCharacter, FString CharacterAmount)
{
    if (InfoDataTable)
    {
        FInformationTable *Row = InfoDataTable->FindRow<FInformationTable>(NameOfCharacter, "CharacterInfo");
        if (Row)
        {
            if(Row->CharacterStatus == ECharacterStatus::ECS_Unlocked)
            {
                PC->SetCharacterWidgetStatusValue(FText::FromString(FString("Selected")));
                return;
            }

            if (GM->Character)
            {
                if (CheckForValidFunds(Row))
                {
                    FVector Location = GM->Character->GetActorLocation();
                    FRotator Rotation = GM->Character->GetActorRotation();
                    GM->Character->Destroy();
                    GM->Character = GetWorld()->SpawnActor<ANLCharacter>(Row->CharacterTclass, Location, Rotation);
                    Row->CharacterStatus = ECharacterStatus::ECS_Unlocked;
                    GM->SaveGame();
                }
                else
                {
                    PC->SetCharacterWidgetStatusValue(FText::FromString(FString::Printf(TEXT("Required %s coins to unlock"), *CharacterAmount)));
                }
            }
        }
    }
}

bool UNLCharacterWidget::CheckForValidFunds(FInformationTable *Row)
{
    if (Row->CharacterStatus == ECharacterStatus::ECS_Unlocked)
        return true;
    if (GM->Coins >= Row->CharacterValue)
    {
        GM->Coins -= Row->CharacterValue;
        if (PC)
        {
            PC->SetCharacterWidgetCoins(GM->Coins);
        }
        return true;
    }
    else
        return false;
}
