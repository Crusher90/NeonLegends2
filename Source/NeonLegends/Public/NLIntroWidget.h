// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "NLIntroWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API UNLIntroWidget : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_CharacterChange;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Play;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Powerups;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Settings;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> IM_Coins;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_CharacterChange;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Play;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Powerups;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Coins;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUserWidget> SettingsWidget;

protected:
	UFUNCTION()
	void ClickedBT_CharacterChange();

	UFUNCTION()
	void ClickedBT_Play();

	UFUNCTION()
	void ClickedBT_Powerups();

	UFUNCTION()
	void ClickedBT_Settings();

public:
	FORCEINLINE UTextBlock *GetCoinsText() const { return TB_Coins; }
};
