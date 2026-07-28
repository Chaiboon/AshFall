// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AshBaseEnemy.h"

#include "AshMeleeEnemy.generated.h"

UCLASS()
class ASHFALL_API AAshMeleeEnemy : public AAshBaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAshMeleeEnemy();

	virtual void PossessedBy(AController* NewController) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};