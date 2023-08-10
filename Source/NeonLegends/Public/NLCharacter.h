// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NLCharacter.generated.h"

UCLASS()
class NEONLEGENDS_API ANLCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANLCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class USpringArmComponent *CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent *FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Buffs")
	class USphereComponent *CoinMagnetSphere;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	class ANLPlayerController *NLPlayerController;

	UPROPERTY(EditAnywhere, Category = "Lane Properties")
	float LaneChangeOffset = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Lane Properties")
	int32 CurrentLaneIndex = 1;

	UPROPERTY(EditAnywhere, Category = "AnimMontages")
	UAnimMontage *CrouchRollMontage;

	UPROPERTY()
	class UAnimInstance *AnimInstance;

	UPROPERTY()
	class AKillActorVolume *KillBox;

	UPROPERTY(EditAnywhere, Category = "KillBox")
	TSubclassOf<AKillActorVolume> KillBoxClass;

	UPROPERTY()
	class ANLCoin *Coin;

	UPROPERTY()
	class ANLGameMode *GM;

	UPROPERTY(EditAnywhere, Category = "CameraMovement")
	TObjectPtr<class AActor> NewViewTarget;

	UPROPERTY(VisibleAnywhere, Category = "Inputs")
	bool bIsInputEnabled = false;

protected:
	void MoveForward(float DeltaTime);

	void ChangeLane(float DeltaTime);

	void AttachKillActorBox();

	UFUNCTION()
	virtual void OnActorBeginOverlapSphere(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void InterpCoins(float DeltaTime);

public:
	FVector2D TouchPressedLocation;

	void TouchPressed(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchReleased(ETouchIndex::Type FingerIndex, FVector Location);

	void SwipeUp();

	void SwipeDown();

	void SwipeLeft();

	void SwipeRight();

	void CheckForLoadGame();

	void SetCameraView();

public:
	FORCEINLINE USphereComponent *GetCoinSphere() const {return CoinMagnetSphere;}

	FORCEINLINE ANLPlayerController *GetNLPlayerController() const {return NLPlayerController;}
	
	FORCEINLINE void SetIsInputEnabled(bool Value) { bIsInputEnabled = Value; }
};
