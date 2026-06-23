// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Attributes/AshEnemyAttributeSet.h"
#include "AshEnemyInterface.h"

#include "AshBaseEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshBaseEnemy : public ACharacter,
								public IAbilitySystemInterface,
								public IAshEnemyInterface
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

	//Override from EnemySystemInterface
	virtual void Damage_Implementation(float Amount) override;
	virtual void Die_Implementation() override;
	virtual AActor* GetAggroTarget_Implementation() const override;


	//Override from AbilitySystemInterface
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAshEnemyAttributeSet* AttributeSet;

	UAshEnemyAttributeSet* GetAttributeSet() const;

	UPROPERTY(EditDefaultsOnly, Category = "DamageEffectClass")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};	

