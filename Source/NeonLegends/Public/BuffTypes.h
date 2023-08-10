#pragma once

UENUM(BlueprintType)
enum class EPickupBuffType : uint8
{
	EPBT_Jump UMETA(DisplayName = "JumpBuff"),
	EPBT_Speed UMETA(DisplayName = "SpeedBuff"),
	EPBT_CoinMagnet UMETA(DisplayName = "CoinMagnet"),
	EPBT_ScoreBooster UMETA(DisplayName = "ScoreBooster"),
	EPBT_CoinBooster UMETA(DisplayName = "CoinBooster"),

	EPBT_Max UMETA(DisplayName = "DefaultMax")
};