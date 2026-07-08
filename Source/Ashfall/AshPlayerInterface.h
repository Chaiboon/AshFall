// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AshPlayerInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UAshPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class ASHFALL_API IAshPlayerInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Damage(FGameplayEffectSpecHandle SpecHandle);
	UFUNCTION(BlueprintNativeEvent)
	void Die();
};
