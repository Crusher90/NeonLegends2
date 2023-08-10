// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLPauseWidget : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Score;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_RunnerCoins;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Resume;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_MainMenu;

protected:
	UFUNCTION()
	void ClickedBT_Resume();

	UFUNCTION()
	void ClickedBT_MainMenu();

public:
	FORCEINLINE UTextBlock *GetScoreText() const { return TB_Score; }
	FORCEINLINE UTextBlock *GetRunnerCoinsText() const { return TB_RunnerCoins; }
};
