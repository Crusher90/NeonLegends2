// Fill out your copyright notice in the Description page of Project Settings.


#include "NLHUD.h"
#include "NLLoadingScreen.h"
#include "NLIntroWidget.h"
#include "NLCharacterWidget.h"
#include "NLPowerupWidget.h"
#include "NLInfoOverlay.h"
#include "NLSettingsWidget.h"
#include "NLDeadScreenWidget.h"

void ANLHUD::BeginPlay()
{
    Super::BeginPlay();
    AddMainOverlay();
    FTimerHandle UITimerHandle;
    GetWorldTimerManager().SetTimer(UITimerHandle, this, &ThisClass::EnableVisiblity, 12.f);
}

void ANLHUD::AddMainOverlay()
{
    if(IntroWidgetClass)
    {
        IntroWidget = CreateWidget<UNLIntroWidget>(GetOwningPlayerController(), IntroWidgetClass);
        IntroWidget->SetVisibility(ESlateVisibility::Hidden);
        IntroWidget->AddToViewport();
    }
    if(CharacterWidgetClass)
    {
        CharacterWidget = CreateWidget<UNLCharacterWidget>(GetOwningPlayerController(), CharacterWidgetClass);
        CharacterWidget->SetVisibility(ESlateVisibility::Hidden);
        CharacterWidget->AddToViewport();
    }
    if(PowerupWidgetClass)
    {
        PowerupWidget = CreateWidget<UNLPowerupWidget>(GetOwningPlayerController(), PowerupWidgetClass);
        PowerupWidget->SetVisibility(ESlateVisibility::Hidden);
        PowerupWidget->AddToViewport();
    }
    if(InfoOverlayClass)
    {
        InfoOverlay = CreateWidget<UNLInfoOverlay>(GetOwningPlayerController(), InfoOverlayClass);
        InfoOverlay->SetVisibility(ESlateVisibility::Hidden);
        InfoOverlay->AddToViewport();
    }
    if (LoadingWidgetClass)
    {
        LoadingWidget = CreateWidget<UNLLoadingScreen>(GetOwningPlayerController(), LoadingWidgetClass);
        LoadingWidget->AddToViewport();
    }
    if(DeadWidgetClass)
    {
        DeadWidget = CreateWidget<UNLDeadScreenWidget>(GetOwningPlayerController(), DeadWidgetClass);
    }
}

void ANLHUD::EnableVisiblity() 
{
    if(IntroWidget)
    {
        IntroWidget->SetVisibility(ESlateVisibility::Visible);
    }
}


