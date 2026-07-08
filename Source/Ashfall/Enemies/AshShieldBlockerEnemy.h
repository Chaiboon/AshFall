// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AshMeleeEnemy.h"
#include "AshEnemyInterface.h"
#include "Attributes/AshBlockerAttributeSet.h"

#include "AshShieldBlockerEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshShieldBlockerEnemy : public AAshMeleeEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAshShieldBlockerEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsAttackBlocked();
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float BlockThreshold;
	UPROPERTY(VisibleAnywhere)
	bool bIsShieldBroke = false;

	virtual void Damage_Implementation(FGameplayEffectSpecHandle SpecHandle) override;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	UAshBlockerAttributeSet* AttributeBlockerSet;

	UPROPERTY(EditDefaultsOnly, Category = "DamageEffectClass")
	TSubclassOf<UGameplayEffect> DamageBlockEffectClass;
};
