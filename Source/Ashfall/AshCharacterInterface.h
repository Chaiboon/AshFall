// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayEffectTypes.h"

#include "AshCharacterInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UAshCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class ASHFALL_API IAshCharacterInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Damage(FGameplayEffectSpecHandle SpecHandle);
	UFUNCTION(BlueprintNativeEvent)
	void Die();
};