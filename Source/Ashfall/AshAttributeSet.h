// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AshAttributeSet.generated.h"
/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
      GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
      GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
      GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
      GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ASHFALL_API UAshAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAshAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;

	ATTRIBUTE_ACCESSORS(UAshAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UAshAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UAshAttributeSet, MaxStamina)
	ATTRIBUTE_ACCESSORS(UAshAttributeSet, Stamina)
};
