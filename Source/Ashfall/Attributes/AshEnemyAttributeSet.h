// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AshAttributeAccessorMacros.h"

#include "AshEnemyAttributeSet.generated.h"

/**
 * 
 */

UCLASS()
class ASHFALL_API UAshEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAshEnemyAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	
	ATTRIBUTE_ACCESSORS(UAshEnemyAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UAshEnemyAttributeSet, Health)
};
