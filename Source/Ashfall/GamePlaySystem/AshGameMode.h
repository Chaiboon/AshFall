// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AshGameMode.generated.h"

/**
 * 
 */
namespace MatchState
{
	extern ASHFALL_API const FName ArenaCleared;
	extern ASHFALL_API const FName SaveRoom;
}

UCLASS()
class ASHFALL_API AAshGameMode : public AGameMode
{
	GENERATED_BODY()
	
	

public:

	AAshGameMode();

	virtual void BeginPlay() override;

	void OnEnemyDied();
	virtual void OnMatchStateSet() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	UPROPERTY(EditDefaultsOnly)
	FName TargetPlayerStartTag = FName("SecondStartingPoint");
};