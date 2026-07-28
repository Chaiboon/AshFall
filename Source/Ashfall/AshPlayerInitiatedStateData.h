// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AshPlayerInitiatedStateData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ASHFALL_API FAshPlayerInitiatedStateData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 InitGold = 0;
};
