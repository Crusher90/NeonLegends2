// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DataLibrary.h"
#include "NLSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSaveGameInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FInformationTable InfoTable;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 Coins = 20000;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float JumpBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float SpeedBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float ScoreMultiplierBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float CoinMultiplierBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float CoinMagnetBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 HighJumpUpgradeThreshold = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 ScoreUpgradeThreshold = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 CoinsUpgradeThreshold = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 CoinMagnetUpgradeThreshold = 500.f;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	int32 HeadStartUpgradeThreshold = 500.f;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float HighJumpUpgradePercent = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float ScoreUpgradePercent = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float CoinsUpgradePercent = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float CoinMagnetUpgradePercent = 0;

	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	float HeadStartUpgradePercent = 0;
};

UCLASS()
class NEONLEGENDS_API UNLSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	FSaveGameInfo SaveGameInfo;
};
