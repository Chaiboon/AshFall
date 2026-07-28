// Fill out your copyright notice in the Description page of Project Settings.


#include "AshArcherEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemies/AshArcherAIController.h"
#include "AshArrowProjectile.h"


// Sets default values
AAshArcherEnemy::AAshArcherEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAshArcherAIController::StaticClass();
}

// Called when the game starts or when spawned
void AAshArcherEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AAshArcherEnemy::Fire()
{
	AAshArcherAIController* MyController = Cast<AAshArcherAIController>(GetController());
	if (!MyController) return;
	if (MyController->GetArcherCurrentState() == ECharacterState::Fleeing) return;
	AActor* Target = Execute_GetAggroTarget(this);
	if (!IsValid(Target)) return;

	MyController->SetArcherCurrentState(ECharacterState::Attacking);
	FVector ActorLocation = this->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FRotator Direction = UKismetMathLibrary::FindLookAtRotation(ActorLocation, TargetLocation);

	GetWorld()->SpawnActor<AAshArrowProjectile>(ArrowProjectile, ActorLocation, Direction);
	MyController->SetArcherCurrentState(ECharacterState::Idle);
}
