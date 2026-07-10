// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AshattributeAccessorMacros.h"

#include "AshBaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAshBaseAttributeSet();

	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly,Category="Attributes")
	FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(UAshBaseAttributeSet,MaxHealth)
	ATTRIBUTE_ACCESSORS(UAshBaseAttributeSet,Health)

};
