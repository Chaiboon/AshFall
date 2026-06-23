// Fill out your copyright notice in the Description page of Project Settings.


#include "AshArcherEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "AshArrowProjectile.h"


// Sets default values
AAshArcherEnemy::AAshArcherEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAshArcherEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentFleeCoolDown = FleeCoolDown;
	CurrentState = ECharacterState::Idle;

	GetWorldTimerManager().SetTimer(
		MyTimerHandle,
		this,
		&AAshArcherEnemy::Fire,
		FiringCoolDown,
		true  
	);
}

// Called every frame
void AAshArcherEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentFleeCoolDown = FMath::Min(CurrentFleeCoolDown += DeltaTime, FleeCoolDown+1.0f);

	AActor* Target = IAshEnemyInterface::Execute_GetAggroTarget(this);
	if (!IsValid(Target)) return;

	if (CurrentFleeCoolDown < FleeCoolDown)
	{
		CurrentState = ECharacterState::Idle;
		return;
	}

	FVector ActorLocation = this->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	if (FVector::Dist(ActorLocation, TargetLocation) < RetreatRange)
	{
		CurrentState = ECharacterState::Fleeing;
		FVector FleeTargetLocation = ActorLocation + ((ActorLocation - TargetLocation).GetSafeNormal2D() * AttackRange);

		FNavLocation ProjectedLocation;
		UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

		if (NavSys && NavSys->ProjectPointToNavigation(FleeTargetLocation, ProjectedLocation))
		{
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController)
			{
				AIController->MoveToLocation(ProjectedLocation.Location);
				CurrentFleeCoolDown = 0;
			}
		}
	}
}

void AAshArcherEnemy::Fire()
{
	if (CurrentState == ECharacterState::Fleeing) return;
	//UE_LOG(LogTemp, Warning, TEXT("Arrow Shooting Attack!"));
	AActor* Target = IAshEnemyInterface::Execute_GetAggroTarget(this);
	if (!IsValid(Target)) return;

	CurrentState = ECharacterState::Attacking;
	FVector ActorLocation = this->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FRotator Direction = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

	GetWorld()->SpawnActor<AAshArrowProjectile>(ArrowProjectile, ActorLocation, Direction);
	CurrentState = ECharacterState::Idle;
}
