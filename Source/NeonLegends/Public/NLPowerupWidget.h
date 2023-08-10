// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLPowerupWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLPowerupWidget : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Characters;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_HighJumpUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_ScoreUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_CoinsUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_CoinMagnetUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_HeadStartUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Characters;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_HighJumpValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_ScoreValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_CoinsValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Coins;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_CoinMagnetValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_HeadStartValue;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_HighJumpUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_ScoreUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_CoinsUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_CoinMagnetUpgrade;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_HeadStartUpgrade;

protected:
	UFUNCTION()
	void ClickedBT_Back();

	UFUNCTION()
	void ClickedBT_Characters();

	UFUNCTION()
	void ClickedBT_HighJumpUpgrade();

	UFUNCTION()
	void ClickedBT_ScoreUpgrade();

	UFUNCTION()
	void ClickedBT_CoinsUpgrade();

	UFUNCTION()
	void ClickedBT_CoinMagnetUpgrade();

	UFUNCTION()
	void ClickedBT_HeadStartUpgrade();

	void ClickedBT_Upgrade(int32 &Threshold, float &Percent, UProgressBar *Bar, UTextBlock *Block, float &BuffTime);

public:
	FORCEINLINE UTextBlock *GetCoinsText() const { return TB_Coins; }
	
};
