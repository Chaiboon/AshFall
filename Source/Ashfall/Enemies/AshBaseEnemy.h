// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Attributes/AshEnemyAttributeSet.h"
#include "AshEnemyInterface.h"
#include "GamePlaySystem/AshGameState.h"
#include "GamePlaySystem/AshGameMode.h"
#include "Abilities/GameplayAbility.h"
#include "GenericTeamAgentInterface.h"
#include "AshBaseCharacter.h"


#include "AshBaseEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshBaseEnemy : public AAshBaseCharacter, public IAshEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAshBaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TWeakObjectPtr<AActor> AggroTarget;
	UPROPERTY()
	AAshGameState* GameState;
	UPROPERTY()
	AAshGameMode* GameMode;

	virtual AActor* GetAggroTarget_Implementation() const override;

	UPROPERTY(EditDefaultsOnly, Category="Ablility")
	TSubclassOf<UGameplayAbility> Ability;

	virtual void Die_Implementation() override;

	UPROPERTY(EditDefaultsOnly)
	FGenericTeamId TeamID = 2;

	UPROPERTY(EditDefaultsOnly)
	float AttackActivationRange = 80.0f;
};	

