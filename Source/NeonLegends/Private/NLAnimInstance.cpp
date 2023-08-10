// Fill out your copyright notice in the Description page of Project Settings.


#include "NLAnimInstance.h"
#include "NLCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNLAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    NLCharacter = NLCharacter == nullptr ? Cast<ANLCharacter>(TryGetPawnOwner()) : NLCharacter;
}

void UNLAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    NLCharacter = NLCharacter == nullptr ? Cast<ANLCharacter>(TryGetPawnOwner()) : NLCharacter;
    if(!NLCharacter)
        return;
    
    FVector Velocity = NLCharacter->GetVelocity();
    Velocity.Z = 0.f;
    Speed = Velocity.Size();

    bIsFalling = NLCharacter->GetCharacterMovement()->IsFalling();

    if(NLCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f){
        bIsAccelerating = true;
    }   
    else{
        bIsAccelerating = false;
    }
}
