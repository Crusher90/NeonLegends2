// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BuffTypes.h"
#include "DataLibrary.h"
#include "NLGameMode.generated.h"

/**
 *
 */
UCLASS()
class NEONLEGENDS_API ANLGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	class ANLTiles *SpawnedTile;

	UPROPERTY(EditAnywhere, Category = "TileProperties")
	TArray<TSubclassOf<ANLTiles>> TileArray;

	FInformationTable InfoTable;

public:
	UPROPERTY()
	class ANLCharacter *Character;

	UPROPERTY()
	class ANLPlayerController *PC;

	UPROPERTY(EditAnywhere, Category = "NLHitActors")
	TSubclassOf<class ANLHitActors> CoinSubclass;

	UPROPERTY(EditAnywhere, Category = "TileProperties")
	TArray<TSubclassOf<class ANLHitActors>> ObstacleArray;

	UPROPERTY(EditAnywhere, Category = "TileProperties")
	TArray<TSubclassOf<class ANLHitActors>> BuffArray;

	UPROPERTY(EditAnywhere, Category = "Legends")
	float LegendSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Legends")
	float LegendSpeedMultiplier = 5.f;

	FTimerHandle JumpBuffTimer;
	FTimerHandle SpeedBuffTimer;
	FTimerHandle CoinMagnetBuffTimer;
	FTimerHandle ScoreMultiplierBuffTimer;
	FTimerHandle CoinMultiplierBuffTimer;
	FTimerHandle ScoreTimerHandle;

	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float JumpBuffTime = 10.f;
	
	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float SpeedBuffTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float LaunchZVelocity = 2000.f;

	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float CoinMagnetBuffTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float ScoreMultiplierBuffTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "BuffTime")
	float CoinMultiplierBuffTime = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "BuffEnum")
	EPickupBuffType BuffType = EPickupBuffType::EPBT_Max;

	UPROPERTY(EditAnywhere, Category="ScoreValue")
	int32 Score = 0;

	UPROPERTY(EditAnywhere, Category="CoinValue")
	int32 Coins = 0;

	UPROPERTY(VisibleAnywhere, Category="CoinValue")
	int32 RunnerCoins = 0;

	UPROPERTY(EditAnywhere, Category = "Multipliers")
	int32 ScoreMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "Multipliers")
	int32 CoinsMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	int32 HighJumpUpgradeThreshold = 500;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	int32 ScoreUpgradeThreshold = 500;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	int32 CoinsUpgradeThreshold = 500;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	int32 CoinMagnetUpgradeThreshold = 500;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	int32 HeadStartUpgradeThreshold = 500;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float HighJumpUpgradePercent = 0;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float ScoreUpgradePercent = 0;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float CoinsUpgradePercent = 0;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float CoinMagnetUpgradePercent = 0;

	UPROPERTY(EditAnywhere, Category = "UpgradeBuffs")
	float HeadStartUpgradePercent = 0;

public:
	void SpawnTiles(FVector Location);

	void SpawnHitActors(FVector Location);

	void ActivateBuff(EPickupBuffType Type);

	void ResetJumpProperties();

	void ResetSpeedProperties();

	void ResetMagnetProperties();

	void ResetScoreMultiplier();

	void ResetCoinsMultiplier();

	void SetScoreTimer();

	void SaveGame();

	void LoadGame();
	
	void SetValuesAfterLoad();
};
