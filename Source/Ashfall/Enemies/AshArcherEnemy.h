// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AshBaseEnemy.h"

class AAshArrowProjectile;

#include "AshArcherEnemy.generated.h"


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle        UMETA(DisplayName = "Idle State"),
	Fleeing     UMETA(DisplayName = "Fleeing State"),
	Attacking   UMETA(DisplayName = "Attacking State"),
	Dead        UMETA(DisplayName = "Dead State")
};

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character State")
	ECharacterState CurrentState;

	FTimerHandle MyTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAshArrowProjectile> ArrowProjectile;

	UFUNCTION()
	void Fire();
};
