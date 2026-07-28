// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AshArcherAIController.h"
#include "AshEnemyInterface.h"
#include "NavigationSystem.h"
#include "AshArrowProjectile.h"
#include "TimerManager.h"
#include "Enemies/AshArcherEnemy.h"

AAshArcherAIController::AAshArcherAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAshArcherAIController::BeginPlay()
{
	Super::BeginPlay();

	AAshArcherEnemy* Acher = Cast<AAshArcherEnemy>(GetPawn());
	if (!Acher) return;

	CurrentFleeCoolDown = FleeCoolDown;
	SetArcherCurrentState(ECharacterState::Idle);

	GetWorldTimerManager().SetTimer(
		MyTimerHandle,
		Acher,
		&AAshArcherEnemy::Fire,
		FiringCoolDown,
		true
	);
}

void AAshArcherAIController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamId = NewTeamID;
}

FGenericTeamId AAshArcherAIController::GetGenericTeamId() const
{
	return TeamId;
}

void AAshArcherAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentFleeCoolDown = FMath::Min(CurrentFleeCoolDown += DeltaTime, FleeCoolDown + 1.0f);

	if (CurrentFleeCoolDown < FleeCoolDown)
	{
		SetArcherCurrentState(ECharacterState::Idle);
		return;
	}

	AActor* ControlledPawn = this->GetPawn();
	if (!ControlledPawn) return;
	AActor* Target = IAshEnemyInterface::Execute_GetAggroTarget(ControlledPawn);
	if (!IsValid(Target)) return;
	
	FVector ActorLocation = ControlledPawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	if (FVector::Dist(ActorLocation, TargetLocation) > RetreatRange) return;
	
	SetArcherCurrentState(ECharacterState::Fleeing);
	FVector FleeTargetLocation = ActorLocation + ((ActorLocation - TargetLocation).GetSafeNormal2D() * AttackRange);

	FNavLocation ProjectedLocation;
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (!NavSys || !NavSys->ProjectPointToNavigation(FleeTargetLocation, ProjectedLocation)) return;

	this->MoveToLocation(ProjectedLocation.Location);
	CurrentFleeCoolDown = 0;
	
}

void AAshArcherAIController::SetArcherCurrentState(ECharacterState NewState)
{
	CurrentState = NewState;
}

ECharacterState AAshArcherAIController::GetArcherCurrentState() const
{
	return CurrentState;
}


