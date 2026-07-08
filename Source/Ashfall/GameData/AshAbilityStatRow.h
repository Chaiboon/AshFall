// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AshAbilityStatRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAshAbilityStatRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float Damage = 0.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float AttackRange = 0.0f;
};
