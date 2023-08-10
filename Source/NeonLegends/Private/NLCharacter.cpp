// Fill out your copyright notice in the Description page of Project Settings.

#include "NLCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NLPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Components/SphereComponent.h"
#include "NLCoin.h"
#include "NeonLegends/NeonLegends.h"
#include "Kismet/GameplayStatics.h"
#include "KillActorVolume.h"
#include "NLGameMode.h"

// Sets default values
ANLCharacter::ANLCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.f;
	CameraBoom->TargetArmLength = 120.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 160.f);
	CameraBoom->bEnableCameraLag = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetAspectRatio(0.462203f);

	CoinMagnetSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CoinMagnetSphere"));
	CoinMagnetSphere->SetupAttachment(GetMesh());
	CoinMagnetSphere->SetSphereRadius(700.f);
	CoinMagnetSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CoinMagnetSphere->SetCollisionObjectType(ECC_Coins);
	CoinMagnetSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CoinMagnetSphere->SetCollisionResponseToChannel(ECC_Coins, ECollisionResponse::ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 400.f;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

// Called when the game starts or when spawned
void ANLCharacter::BeginPlay()
{
	Super::BeginPlay();
	NLPlayerController = Cast<ANLPlayerController>(GetController());
	GM = Cast<ANLGameMode>(UGameplayStatics::GetGameMode(this));
	AnimInstance = GetMesh()->GetAnimInstance();
	AttachKillActorBox();
	CoinMagnetSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorBeginOverlapSphere);
}

// Called every frame
void ANLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(DeltaTime);
	ChangeLane(DeltaTime);
	InterpCoins(DeltaTime);
}

// Called to bind functionality to input
void ANLCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ThisClass::TouchPressed);
	PlayerInputComponent->BindTouch(IE_Released, this, &ThisClass::TouchReleased);
}

void ANLCharacter::CheckForLoadGame() 
{
	if (UGameplayStatics::DoesSaveGameExist(FString("SaveGameSlot"), 0))
	{
		if(GM)
		{
			GM->LoadGame();
			NLPlayerController->SetIntroCoins(GM->Coins);
		}
	}
}

void ANLCharacter::TouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchPressedLocation = FVector2D(Location);
}

void ANLCharacter::TouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bIsInputEnabled == false)
		return;
	FVector2D TouchDelta = FVector2D(Location) - TouchPressedLocation;
	if (TouchDelta.X < -50.f && CurrentLaneIndex > 0)
	{
		SwipeLeft();
		CurrentLaneIndex--;
	}
	else if (TouchDelta.X > 50.f && CurrentLaneIndex < 2)
	{
		SwipeRight();
		CurrentLaneIndex++;
	}
	if (TouchDelta.Y < -50.f)
	{
		SwipeUp();
	}
	else if (TouchDelta.Y > 50.f)
	{
		SwipeDown();
	}
}

void ANLCharacter::SwipeUp()
{
	ThisClass::Jump();
}

void ANLCharacter::SwipeDown()
{
	ThisClass::StopJumping();
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->AddImpulse(FVector(0.f, 0.f, -3000.f), true);
		return;
	}
	if (AnimInstance && CrouchRollMontage)
	{
		if (AnimInstance->Montage_IsActive(CrouchRollMontage))
			return;
		Crouch();
		AnimInstance->Montage_Play(CrouchRollMontage);
	}
}

void ANLCharacter::SwipeLeft()
{
	LaneChangeOffset = -330.f;
}

void ANLCharacter::SwipeRight()
{
	LaneChangeOffset = 330.f;
}

void ANLCharacter::MoveForward(float DeltaTime)
{
	if(bIsInputEnabled == false)
		return;
	AddMovementInput(GetActorForwardVector(), GetCharacterMovement()->MaxWalkSpeed * DeltaTime);
}

void ANLCharacter::ChangeLane(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLaneIndex == 1)
	{
		CurrentLocation.Y = UKismetMathLibrary::FInterpTo(CurrentLocation.Y, 0.f, DeltaTime, 10.f);
		SetActorLocation(CurrentLocation);
	}
	else
	{
		CurrentLocation.Y = UKismetMathLibrary::FInterpTo(CurrentLocation.Y, LaneChangeOffset, DeltaTime, 10.f);
		SetActorLocation(CurrentLocation);
	}
}

void ANLCharacter::AttachKillActorBox()
{
	if (KillBoxClass)
	{
		KillBox = GetWorld()->SpawnActor<AKillActorVolume>(KillBoxClass, GetMesh()->GetComponentLocation() + FVector(-3000.f, 0.f, 0.f), FRotator::ZeroRotator);
		if (KillBox)
		{
			KillBox->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void ANLCharacter::OnActorBeginOverlapSphere(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!OtherActor)
		return;
	Coin = Cast<ANLCoin>(OtherActor);
}

void ANLCharacter::InterpCoins(float DeltaTime)
{
	if (Coin && GM && GM->CoinMagnetBuffTimer.IsValid())
	{
		FVector NewLocation = FMath::VInterpTo(Coin->GetActorLocation(), GetActorLocation(), DeltaTime, 30.f);
		Coin->SetActorLocation(NewLocation);
	}
}

void ANLCharacter::SetCameraView()
{
	if (NLPlayerController && NewViewTarget)
	{
		NLPlayerController->SetViewTargetWithBlend(NewViewTarget, 5.f, EViewTargetBlendFunction::VTBlend_Cubic);
	}
}
