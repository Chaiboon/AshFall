// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Animation/AnimMontage.h"
#include "AshBaseInstantDamageAbility.h"

#include "AshChargeAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshChargeAttackAbility : public UAshBaseInstantDamageAbility
{
	GENERATED_BODY()
	
public:

	UAshChargeAttackAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Animation")
	UAnimMontage* ChargeAnimMontageToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* ReleaseAnimMontageToPlay;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	
	UFUNCTION()
	void OnRelease(float TimeHeld);
	UPROPERTY(EditDefaultsOnly,Category = "Charge")
	float MaxChargeTime = 2.0f;
	UPROPERTY(EditDefaultsOnly,Category = "Charge")
	float MinChargeTime = 0.2f;
	UPROPERTY(VisibleAnywhere)
	float ChargeStartTime;
	float ChargePercent = 0.0f;
	bool bIsReleasing = false;

	UFUNCTION()
	void OnChargeMontageCompleted();
	UFUNCTION()
	void OnChargeMontageCancelled();
	UFUNCTION()
	void OnReleaseMontageCompleted();
	UFUNCTION()
	void OnReleaseeMontageCancelled();

	virtual float GetDamageAmount() const override;
	virtual float GetAttackRange() const override;
};