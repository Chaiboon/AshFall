// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AshAttributeAccessorMacros.h"
#include "AshBlockerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshBlockerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAshBlockerAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxBlockHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData BlockHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MoveSpeedMultiplier;

	ATTRIBUTE_ACCESSORS(UAshBlockerAttributeSet, MaxBlockHealth)
	ATTRIBUTE_ACCESSORS(UAshBlockerAttributeSet, BlockHealth)
	ATTRIBUTE_ACCESSORS(UAshBlockerAttributeSet, MoveSpeedMultiplier)
};
