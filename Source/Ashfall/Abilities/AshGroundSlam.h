// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "AshGroundSlam.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshGroundSlam : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly)
	float GroundSlamLaunchRadius = 1500.0f;
	UPROPERTY(EditDefaultsOnly)
	float GroundSlamKnockbackSpeed = 700.0f;
	UPROPERTY(EditDefaultsOnly)
	float GroundSlamKnockbackHeight = 100.0f;
};
