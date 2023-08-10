// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NLGameMode.h"
#include "NLPlayerController.h"
#include "NLParentWidget.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API UNLParentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

	UPROPERTY()
	TObjectPtr<class ANLGameMode> GM;

	UPROPERTY()
	TObjectPtr<class ANLPlayerController> PC;
};
