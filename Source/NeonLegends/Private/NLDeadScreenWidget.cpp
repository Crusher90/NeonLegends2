// Fill out your copyright notice in the Description page of Project Settings.


#include "NLDeadScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UNLDeadScreenWidget::Initialize()
{
    if(!Super::Initialize())
    return false;

    if(BT_MainMenu)
    {
        BT_MainMenu->OnClicked.AddDynamic(this, &ThisClass::ClickedBT_MainMenu);
    }
    return true;
}

void UNLDeadScreenWidget::ClickedBT_MainMenu()
{
    GM->SaveGame();
    UGameplayStatics::OpenLevel(this, FName("Map1"));
}
