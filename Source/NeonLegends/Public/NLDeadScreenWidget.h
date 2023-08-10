// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLDeadScreenWidget.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API UNLDeadScreenWidget : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void ClickedBT_MainMenu();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Score;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_RunnerCoins;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_MainMenu;

public:
	FORCEINLINE UTextBlock *GetScoreText() const { return TB_Score; }
	FORCEINLINE UTextBlock *GetRunnerCoinsText() const { return TB_RunnerCoins; }
};
