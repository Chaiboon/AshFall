// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AshAttributeAccessorMacros.h"
#include "Attributes/AshBaseAttributeSet.h"
#include "AshAttributeSet.generated.h"
/**
 * 
 */

UCLASS()
class ASHFALL_API UAshAttributeSet : public UAshBaseAttributeSet
{
	GENERATED_BODY()

public:
	UAshAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;

	ATTRIBUTE_ACCESSORS(UAshAttributeSet, MaxStamina)
	ATTRIBUTE_ACCESSORS(UAshAttributeSet, Stamina)
};
