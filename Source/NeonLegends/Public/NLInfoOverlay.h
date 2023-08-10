// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLInfoOverlay.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLInfoOverlay : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TB_Score;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TB_Coins;

	UPROPERTY(meta = (BindWidget))
	class UButton *BT_Pause;

	UPROPERTY(meta = (BindWidget))
	class UButton *BT_HeadStart;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNLPauseWidget> PauseWidget;

protected:
	UFUNCTION()
	void ClickedBT_Pause();

	UFUNCTION()
	void ClickedBT_HeadStart();

	void DisableHeadStartButton();

public:
	FTimerHandle DisableHeadStartTimer;
	FORCEINLINE UTextBlock *GetScoreText() const { return TB_Score; }
	FORCEINLINE UTextBlock *GetCoinsText() const { return TB_Coins; }
};
