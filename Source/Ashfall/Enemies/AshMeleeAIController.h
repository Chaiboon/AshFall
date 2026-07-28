// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "Enemies/AshMeleeEnemy.h"

#include "AshMeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API AAshMeleeAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	AAshMeleeAIController();

protected:
	virtual void BeginPlay() override;

private:
	FGenericTeamId TeamId;
	UPROPERTY()
	AAshMeleeEnemy* ControlledPawn;


public:

	//IGenericTeamAgentInterface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId  GetGenericTeamId() const override;

	virtual void Tick(float DeltaTime) override;
};
