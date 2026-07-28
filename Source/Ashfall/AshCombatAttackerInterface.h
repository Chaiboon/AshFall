// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "AshCombatAttackerInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UAshCombatAttackerInterface : public UInterface
{
	GENERATED_BODY()
};

class ASHFALL_API IAshCombatAttackerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void CheckAttack(FGameplayTag EventTag);
	UFUNCTION(BlueprintNativeEvent)
	FGameplayTag GetGameplayTag();
	UFUNCTION(BlueprintNativeEvent)
	void SetGameplayTag(FGameplayTag EventTag);
	UFUNCTION(BlueprintNativeEvent)
	FString GetAbilityDataTag();
	UFUNCTION(BlueprintNativeEvent)
	void SetAbilityDataTag(const FString& AbilityDataTag);
};