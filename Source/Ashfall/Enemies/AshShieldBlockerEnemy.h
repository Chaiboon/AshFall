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

private:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.0", ClampMax = "1.0", AllowPrivateAccess= "true"))
	float MovementSpeedDebuffMultiplier = 0.8f;
	float BaseWalkSpeed;
	FActiveGameplayEffectHandle SlowMovementEffectHandler;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsAttackBlocked();
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float BlockThreshold;

	float GetMovementSpeedDebuffMultiplier();

	float GetBaseWalkSpeed();
	void SetBaseWalkSpeed(float NewBaseWalkSpeed);

	FActiveGameplayEffectHandle GetSlowMovementEffectHandler();
	void SetSlowMovementEffectHandler(FActiveGameplayEffectHandle NewSlowMovementEffectHandler);
	UPROPERTY(VisibleAnywhere)
	bool bIsShieldBroke = false;

	virtual void Damage_Implementation(FGameplayEffectSpecHandle SpecHandle) override;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	UAshBlockerAttributeSet* AttributeBlockerSet;

	UPROPERTY(EditDefaultsOnly, Category = "EffectClass")
	TSubclassOf<UGameplayEffect> DamageBlockEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "EffectClass")
	TSubclassOf<UGameplayEffect> MovementImparingEffectClass;
};
