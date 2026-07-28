// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AshMeleeAIController.h"
#include "AshEnemyInterface.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Enemies/AshMeleeEnemy.h"
//#include "AbilitySystemComponent.h"

AAshMeleeAIController::AAshMeleeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAshMeleeAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledPawn = Cast<AAshMeleeEnemy>(GetPawn());
}

void AAshMeleeAIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamId = NewTeamID;
}

FGenericTeamId AAshMeleeAIController::GetGenericTeamId() const
{
	return TeamId;
}

void AAshMeleeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ControlledPawn) return;
	AActor* Target = IAshEnemyInterface::Execute_GetAggroTarget(ControlledPawn);
	if (!IsValid(Target)) return;

	UAIBlueprintHelperLibrary::SimpleMoveToActor(this, Target);

	if (FVector::Dist(ControlledPawn->GetActorLocation(), Target->GetActorLocation()) <= ControlledPawn->AttackActivationRange)
	{
		UAbilitySystemComponent* PawnASC = ControlledPawn->AbilitySystemComponent;

		if (!IsValid(PawnASC)) return;
		PawnASC->TryActivateAbilityByClass(ControlledPawn->Ability);
	}
}
