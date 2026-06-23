// Fill out your copyright notice in the Description page of Project Settings.


#include "AshMeleeEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"

// Sets default values
AAshMeleeEnemy::AAshMeleeEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAshMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAshMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* Target = IAshEnemyInterface::Execute_GetAggroTarget(this);
	if (!IsValid(Target)) return;

	UAIBlueprintHelperLibrary::SimpleMoveToActor(this->GetController(), Target);

	if (FVector::Dist(this->GetActorLocation(), Target->GetActorLocation()) <= AttackRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Melee Attacking!!"));
	}
}