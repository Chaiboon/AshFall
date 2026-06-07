// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AshEnemyInterface.h"
#include "AshMeleeEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshMeleeEnemy : public ACharacter, public IAshEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAshMeleeEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TWeakObjectPtr<AActor> AggroTarget;
	
	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 50.0f;

	// IAshEnemyInterface implementation
	virtual void Damage(float Amount) override;
	virtual void Die() override;
	virtual AActor* GetAggroTarget() const override;
};
