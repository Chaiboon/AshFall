// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameData/AshAbilityStatRow.h"
#include "AbilitySystemComponent.h"

#include "AshBaseInstantDamageAbility.generated.h"
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ASHFALL_API UAshBaseInstantDamageAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	virtual float GetDamageAmount() const PURE_VIRTUAL(UAshInstantDamageAbility::GetDamageAmount, return 0.f;);
	virtual float GetAttackRange() const PURE_VIRTUAL(UAshInstantDamageAbility::GetAttackRange, return 0.f;);
protected:
	UFUNCTION()
	void OnHitEventReceived(FGameplayEventData Payload);
	FAshAbilityStatRow* GetAbilityData(FString AbilityName,int32 Level) const;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly,Category="GamePlayEffect")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
