// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Animation/AnimMontage.h"
#include "AshBaseInstantDamageAbility.h"

#include "AshLightAttack.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshLightAttack : public UAshBaseInstantDamageAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* AnimMontageToPlay;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled();

	virtual float GetDamageAmount() const override;
	virtual float GetAttackRange() const override;
};
