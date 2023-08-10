// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NLPlayerController.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API ANLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANLPlayerController();

	UPROPERTY()
	TObjectPtr<class ANLHUD> NLHUD;

private:
	FTimerHandle ScoreTimerHandle;

protected:
	virtual void BeginPlay() override;

public:
	void SetHUDScore(int32 Score);

	void SetHUDCoins(int32 Coins);

	void SetIntroCoins(int32 Coins);

	void SetCharacterWidgetCoins(int32 Coins);

	void SetPowerupWidgetCoins(int32 Coins);

	void SetCharacterWidgetStatusValue(FText Value);

	void ShowEndGameScreen();

	void SetThresholdValuesAfterLoad(float CoinMagnetValue, float CoinsValue, float HeadStartValue, float HighJumpValue, float ScoreValue);

	void SetProgressBarValuesAfterLoad(float CoinMagnetUpgrade, float CoinsUpgrade, float HeadStartUpgrade, float HighJumpUpgrade, float ScoreUpgrade);
};
