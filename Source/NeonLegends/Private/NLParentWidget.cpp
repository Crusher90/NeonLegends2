// Fill out your copyright notice in the Description page of Project Settings.


#include "NLParentWidget.h"

bool UNLParentWidget::Initialize()
{
    if(!Super::Initialize())
        return false;

    GM = Cast<ANLGameMode>(GetWorld()->GetAuthGameMode());
    PC = Cast<ANLPlayerController>(GetOwningPlayer());
    if(GM && PC)
        return true;

    return false;
}
