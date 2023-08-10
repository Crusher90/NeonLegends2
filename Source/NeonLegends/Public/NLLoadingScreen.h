// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NLLoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLLoadingScreen : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> IM_Background;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBackgroundBlur> BB_Background;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_LoadingBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_LoadingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UThrobber> TH_LoadingLogo;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> WA_LoadingAnimation;

	bool bIsPlaying;

protected:
	virtual bool Initialize() override;

	void OnAnimationStoppedPlaying();
};
