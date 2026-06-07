// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AshfallCharacter.h"
#include "AshDodgeRoll.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshDodgeRoll : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditAnywhere)
	float DodgeRollLaunchStrength = 1500.0f;
	UPROPERTY(EditAnywhere)
	float DodgeRollLaunchZAxis = 300.0f;
	UPROPERTY(EditAnywhere)
	float InvincibilityDuration = 0.5f;
	UPROPERTY()
	AAshfallCharacter* AshfallCharacter;

	FTimerHandle InvincibilityTimer;
	void OnInvicibilityEnd();
};