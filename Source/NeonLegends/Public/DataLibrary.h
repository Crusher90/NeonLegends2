// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataLibrary.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class ECharacterStatus : uint8
{
	ECS_Locked UMETA(DisplayName = "Locked"),
	ECS_Unlocked UMETA(DisplayName = "Unlocked"),

	ECS_Max UMETA(DisplayName = DefaultMax)
};

USTRUCT(BlueprintType)
struct FInformationTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	ECharacterStatus CharacterStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	TSubclassOf<class ACharacter> CharacterTclass;

	UPROPERTY(EditAnywhere, Category = "ItemInfo")
	float CharacterValue;
};

UCLASS()
class NEONLEGENDS_API UDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	// public:
	// 	FInformationTable InfoTable;
	// 	FInformationTable GetInfoTable() { return InfoTable; }
	// 	void SetInfoTable(FInformationTable Value) { InfoTable = Value; }
};
