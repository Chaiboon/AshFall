// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"


#include "AshGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnArenaCleared);

UCLASS()
class ASHFALL_API AAshGameState : public AGameStateBase
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleDefaultsOnly)
	int32 EnemyCount = 0;


public:
	
	UPROPERTY(BlueprintAssignable,Category = "Combat")
	FOnArenaCleared OnArenaCleared;

	void SetEnemyCount(int32 NewEnemyCount);
	void AddEnemyCount(int32 EnemyToAdd);
	int32 GetEnemyCount() const;

};
