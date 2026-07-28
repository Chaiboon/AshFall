// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AshBaseEnemy.h"

class AAshArrowProjectile;

#include "AshArcherEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshArcherEnemy : public AAshBaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAshArcherEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAshArrowProjectile> ArrowProjectile;

	UFUNCTION()
	void Fire();
};
