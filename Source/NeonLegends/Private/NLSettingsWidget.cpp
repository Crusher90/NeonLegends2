// Fill out your copyright notice in the Description page of Project Settings.


#include "NLSettingsWidget.h"
#include "Components/Slider.h"
#include "Components/CheckBox.h"

bool UNLSettingsWidget::Initialize()
{
    if(!Super::Initialize())
        return false;
    if(CB_Vibration)
    {
        CB_Vibration->OnCheckStateChanged.AddDynamic(this, &ThisClass::OnCheckedStateChanged_Vibration);
    }
    return true;
}

void UNLSettingsWidget::OnCheckedStateChanged_Vibration(bool Value)
{
    GetOwningPlayer()->bForceFeedbackEnabled = Value;
}
