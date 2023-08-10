// Fill out your copyright notice in the Description page of Project Settings.

#include "NLGameMode.h"
#include "NLTiles.h"
#include "NLHitActors.h"
#include "NLCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NeonLegends/NeonLegends.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "NLPLayerController.h"
#include "NLSaveGame.h"

void ANLGameMode::BeginPlay()
{
    Character = Cast<ANLCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (Character)
    {
        PC = Cast<ANLPlayerController>(Character->GetController());
    }
    if (!SpawnedTile)
    {
        SpawnTiles(FVector::ZeroVector + FVector(0.f, 0.f, 0.f));
    }
    if (SpawnedTile)
    {
        for (int i = 0; i < 10; i++)
        {
            SpawnTiles(SpawnedTile->TileSpawnLocation);
        }
    }
}

void ANLGameMode::SpawnTiles(FVector Location)
{
    int32 RandTiles = FMath::RandRange(0, TileArray.Num() - 1);
    if (TileArray.Num() > 0 && TileArray[RandTiles])
    {
        UE_LOG(LogTemp, Warning, TEXT("main character valid"));
        SpawnedTile = GetWorld()->SpawnActor<ANLTiles>(TileArray[RandTiles], Location, FRotator::ZeroRotator);
    }
}

void ANLGameMode::SpawnHitActors(FVector Location)
{
    int32 RandInt = FMath::RandRange(0, 9);
    if (RandInt >= 0 && RandInt <= 5)
    {
        if (CoinSubclass)
        {
            GetWorld()->SpawnActor<ANLHitActors>(CoinSubclass, Location, FRotator::ZeroRotator);
            return;
        }
    }
    else if (RandInt > 5 && RandInt <= 8)
    {
        int32 RandNumber = FMath::RandRange(0, ObstacleArray.Num() - 1);
        if (ObstacleArray[RandNumber])
        {
            GetWorld()->SpawnActor<ANLHitActors>(ObstacleArray[RandNumber], Location, FRotator::ZeroRotator);
            return;
        }
    }
    else
    {
        int32 RandNumber = FMath::RandRange(0, BuffArray.Num() - 1);
        if (BuffArray[RandNumber])
        {
            GetWorld()->SpawnActor<ANLHitActors>(BuffArray[RandNumber], Location, FRotator::ZeroRotator);
        }
    }
}

void ANLGameMode::ActivateBuff(EPickupBuffType Type)
{
    if (BuffType == EPickupBuffType::EPBT_Speed)
        return;
    switch (Type)
    {
    case EPickupBuffType::EPBT_Jump:
        GetWorldTimerManager().ClearTimer(JumpBuffTimer);
        GetWorldTimerManager().SetTimer(JumpBuffTimer, this, &ThisClass::ResetJumpProperties, JumpBuffTime);
        BuffType = Type;
        Character->GetCharacterMovement()->JumpZVelocity = 1000.f;
        break;

    case EPickupBuffType::EPBT_Speed:
        GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
        GetWorldTimerManager().SetTimer(SpeedBuffTimer, this, &ThisClass::ResetSpeedProperties, SpeedBuffTime);
        BuffType = Type;
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
        Character->GetCharacterMovement()->MaxFlySpeed = 5000.f;
        Character->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Obstacles, ECollisionResponse::ECR_Ignore);
        break;

    case EPickupBuffType::EPBT_ScoreBooster:
        GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
        GetWorldTimerManager().SetTimer(ScoreMultiplierBuffTimer, this, &ThisClass::ResetScoreMultiplier, ScoreMultiplierBuffTime);
        BuffType = Type;
        ScoreMultiplier = 2;
        break;

    case EPickupBuffType::EPBT_CoinBooster:
        GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
        GetWorldTimerManager().SetTimer(CoinMultiplierBuffTimer, this, &ThisClass::ResetCoinsMultiplier, CoinMultiplierBuffTime);
        BuffType = Type;
        CoinsMultiplier = 2;
        break;

    case EPickupBuffType::EPBT_CoinMagnet:
        GetWorldTimerManager().ClearTimer(CoinMagnetBuffTimer);
        GetWorldTimerManager().SetTimer(CoinMagnetBuffTimer, this, &ThisClass::ResetMagnetProperties, CoinMagnetBuffTime);
        BuffType = Type;
        Character->GetCoinSphere()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        break;

    default:
        break;
    }
}

void ANLGameMode::ResetJumpProperties()
{
    if (Character)
    {
        GetWorldTimerManager().ClearTimer(JumpBuffTimer);
        Character->GetCharacterMovement()->JumpZVelocity = 600.f;
        BuffType = EPickupBuffType::EPBT_Max;
    }
}

void ANLGameMode::ResetSpeedProperties()
{
    if (Character)
    {
        GetWorldTimerManager().ClearTimer(SpeedBuffTimer);
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        Character->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Obstacles, ECollisionResponse::ECR_Block);
        BuffType = EPickupBuffType::EPBT_Max;
    }
}

void ANLGameMode::ResetMagnetProperties()
{
    GetWorldTimerManager().ClearTimer(CoinMagnetBuffTimer);
    Character->GetCoinSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BuffType = EPickupBuffType::EPBT_Max;
}

void ANLGameMode::SetScoreTimer()
{
    FTimerManager &TimerManager = GetWorld()->GetTimerManager();

    FTimerDelegate TimerCallback;
    TimerCallback.BindLambda([=]()
                             {
            Score += 1 * ScoreMultiplier;
        PC->SetHUDScore(Score); });
    TimerManager.SetTimer(ScoreTimerHandle, TimerCallback, 1.f, true);
}

void ANLGameMode::ResetScoreMultiplier()
{
    GetWorldTimerManager().ClearTimer(ScoreMultiplierBuffTimer);
    ScoreMultiplier = 1;
    BuffType = EPickupBuffType::EPBT_Max;
}

void ANLGameMode::ResetCoinsMultiplier()
{
    GetWorldTimerManager().ClearTimer(CoinMultiplierBuffTimer);
    CoinsMultiplier = 1;
    BuffType = EPickupBuffType::EPBT_Max;
}

void ANLGameMode::SaveGame()
{
    UNLSaveGame *SG = Cast<UNLSaveGame>(UGameplayStatics::CreateSaveGameObject(UNLSaveGame::StaticClass()));
    if (SG)
    {
        SG->SaveGameInfo.CoinMagnetBuffTime = CoinMagnetBuffTime;
        SG->SaveGameInfo.CoinMagnetUpgradeThreshold = CoinMagnetUpgradeThreshold;
        SG->SaveGameInfo.CoinMultiplierBuffTime = CoinMultiplierBuffTime;
        SG->SaveGameInfo.Coins = Coins;
        SG->SaveGameInfo.CoinsUpgradeThreshold = CoinsUpgradeThreshold;
        SG->SaveGameInfo.HeadStartUpgradeThreshold = HeadStartUpgradeThreshold;
        SG->SaveGameInfo.HighJumpUpgradeThreshold = HighJumpUpgradeThreshold;
        SG->SaveGameInfo.InfoTable.CharacterStatus = InfoTable.CharacterStatus;
        SG->SaveGameInfo.InfoTable.CharacterTclass = InfoTable.CharacterTclass;
        SG->SaveGameInfo.InfoTable.CharacterValue = InfoTable.CharacterValue;
        SG->SaveGameInfo.JumpBuffTime = JumpBuffTime;
        SG->SaveGameInfo.ScoreMultiplierBuffTime = ScoreMultiplierBuffTime;
        SG->SaveGameInfo.ScoreUpgradeThreshold = ScoreUpgradeThreshold;
        SG->SaveGameInfo.SpeedBuffTime = SpeedBuffTime;
        SG->SaveGameInfo.CoinsUpgradePercent = CoinsUpgradePercent;
        SG->SaveGameInfo.ScoreUpgradePercent = ScoreUpgradePercent;
        SG->SaveGameInfo.HighJumpUpgradePercent = HighJumpUpgradePercent;
        SG->SaveGameInfo.HeadStartUpgradePercent = HeadStartUpgradePercent;
        SG->SaveGameInfo.CoinMagnetUpgradePercent = CoinMagnetUpgradePercent;
        UGameplayStatics::SaveGameToSlot(SG, FString("SaveGameSlot"), 0);
    }
}

void ANLGameMode::LoadGame()
{
    UNLSaveGame *LG = Cast<UNLSaveGame>(UGameplayStatics::CreateSaveGameObject(UNLSaveGame::StaticClass()));
    if (LG)
    {
        LG = Cast<UNLSaveGame>(UGameplayStatics::LoadGameFromSlot(FString("SaveGameSlot"), 0));
        CoinMagnetBuffTime = LG->SaveGameInfo.CoinMagnetBuffTime;
        CoinMagnetUpgradeThreshold = LG->SaveGameInfo.CoinMagnetUpgradeThreshold;
        CoinMultiplierBuffTime = LG->SaveGameInfo.CoinMultiplierBuffTime;
        Coins = LG->SaveGameInfo.Coins;
        CoinsUpgradeThreshold = LG->SaveGameInfo.CoinsUpgradeThreshold;
        HeadStartUpgradeThreshold = LG->SaveGameInfo.HeadStartUpgradeThreshold;
        HighJumpUpgradeThreshold = LG->SaveGameInfo.HighJumpUpgradeThreshold;
        InfoTable.CharacterStatus = LG->SaveGameInfo.InfoTable.CharacterStatus;
        InfoTable.CharacterTclass = LG->SaveGameInfo.InfoTable.CharacterTclass;
        InfoTable.CharacterValue = LG->SaveGameInfo.InfoTable.CharacterValue;
        JumpBuffTime = LG->SaveGameInfo.JumpBuffTime;
        ScoreMultiplierBuffTime = LG->SaveGameInfo.ScoreMultiplierBuffTime;
        ScoreUpgradeThreshold = LG->SaveGameInfo.ScoreUpgradeThreshold;
        SpeedBuffTime = LG->SaveGameInfo.SpeedBuffTime;
        CoinsUpgradePercent = LG->SaveGameInfo.CoinsUpgradePercent;
        ScoreUpgradePercent = LG->SaveGameInfo.ScoreUpgradePercent;
        HighJumpUpgradePercent = LG->SaveGameInfo.HighJumpUpgradePercent;
        HeadStartUpgradePercent = LG->SaveGameInfo.HeadStartUpgradePercent;
        CoinMagnetUpgradePercent = LG->SaveGameInfo.CoinMagnetUpgradePercent;
        SetValuesAfterLoad();
    }
}

void ANLGameMode::SetValuesAfterLoad()
{
    if (PC)
    {
        PC->SetThresholdValuesAfterLoad(CoinMagnetUpgradeThreshold, CoinsUpgradeThreshold, HeadStartUpgradeThreshold, HighJumpUpgradeThreshold, ScoreUpgradeThreshold);
        PC->SetProgressBarValuesAfterLoad(CoinMagnetUpgradePercent, CoinsUpgradePercent, HeadStartUpgradePercent, HighJumpUpgradePercent, ScoreUpgradePercent);
    }
}
