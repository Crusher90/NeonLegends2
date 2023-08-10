// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NLParentWidget.h"
#include "DataLibrary.h"
#include "NLCharacterWidget.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API UNLCharacterWidget : public UNLParentWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> SB_Character;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Michelle;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Amy;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Eve;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Jackie;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_James;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Joe;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Kachujin;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Shannon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Powerups;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> BT_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Back;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Powerups;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Status;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TB_Coins;

	UPROPERTY(EditAnywhere, Category = "InfoData")
	TObjectPtr<class UDataTable> InfoDataTable;

protected:
	void SetCharacterInGame(FName NameOfCharacter, FString CharacterAmount);

	UFUNCTION()
	void ClickedBT_Michelle();

	UFUNCTION()
	void ClickedBT_Amy();

	UFUNCTION()
	void ClickedBT_Eve();

	UFUNCTION()
	void ClickedBT_Jackie();

	UFUNCTION()
	void ClickedBT_James();

	UFUNCTION()
	void ClickedBT_Joe();

	UFUNCTION()
	void ClickedBT_Kachujin();

	UFUNCTION()
	void ClickedBT_Shannon();

	UFUNCTION()
	void ClickedBT_Back();

	UFUNCTION()
	void ClickedBT_Powerups();

	bool CheckForValidFunds(FInformationTable *Row);

public:
	FORCEINLINE UTextBlock *GetCoinsText() const { return TB_Coins; }
	FORCEINLINE UTextBlock *GetStatusText() const { return TB_Status; }
};
