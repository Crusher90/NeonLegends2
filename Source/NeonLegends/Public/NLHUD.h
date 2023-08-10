// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NLHUD.generated.h"

/**
 * 
 */
UCLASS()
class NEONLEGENDS_API ANLHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<class UNLIntroWidget> IntroWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> IntroWidgetClass;

	UPROPERTY()
	TObjectPtr<class UNLInfoOverlay> InfoOverlay;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> InfoOverlayClass;

	UPROPERTY()
	TObjectPtr<class UNLCharacterWidget> CharacterWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterWidgetClass;

	UPROPERTY()
	TObjectPtr<class UNLPowerupWidget> PowerupWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> PowerupWidgetClass;

	UPROPERTY()
	TObjectPtr<class UNLLoadingScreen> LoadingWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> LoadingWidgetClass;

	UPROPERTY()
	TObjectPtr<class UNLDeadScreenWidget> DeadWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> DeadWidgetClass;

protected:
	virtual void BeginPlay() override;

	void AddMainOverlay();
	void EnableVisiblity();
};
