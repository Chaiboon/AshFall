// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AshPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API AAshPlayerState : public APlayerState
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleDefaultsOnly)
	int32 Gold = 0;
	UPROPERTY(VisibleDefaultsOnly)
	int32 Experience = 0;


public:

	void SetGold(int32 NewGold);
	void AddGold(int32 Amount);
	int32 GetGold() const;

	void SetExperience(int32 NewExperience);
	void AddExperience(int32 Amount);
	int32 GetExperience() const;
};
