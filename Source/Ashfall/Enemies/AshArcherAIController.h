// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"

#include "AshArcherAIController.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle        UMETA(DisplayName = "Idle State"),
	Fleeing     UMETA(DisplayName = "Fleeing State"),
	Attacking   UMETA(DisplayName = "Attacking State"),
	Dead        UMETA(DisplayName = "Dead State")
};
/**
 * 
 */
UCLASS()
class ASHFALL_API AAshArcherAIController : public AAIController
{
	GENERATED_BODY()

public:

	AAshArcherAIController();

	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual void Tick(float DeltaTime) override;

	void SetArcherCurrentState(ECharacterState NewState);
	ECharacterState GetArcherCurrentState() const;
private:

	FGenericTeamId TeamId;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 700.0f;
	UPROPERTY(EditDefaultsOnly)
	float RetreatRange = 350.0f;
	UPROPERTY(EditDefaultsOnly)
	float FleeCoolDown = 2.0f;
	UPROPERTY(VisibleAnywhere)
	float CurrentFleeCoolDown;
	UPROPERTY(EditDefaultsOnly)
	float FiringCoolDown = 2.0f;
	UPROPERTY()
	ECharacterState CurrentState;

	FTimerHandle MyTimerHandle;
protected:

	virtual void BeginPlay() override;
};
