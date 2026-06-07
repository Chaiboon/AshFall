// Fill out your copyright notice in the Description page of Project Settings.


#include "AshMeleeEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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
	
	AggroTarget = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AAshMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* Target = GetAggroTarget();
	if (!Target) return;

	UAIBlueprintHelperLibrary::SimpleMoveToActor(this->GetController(), Target);

	if (FVector::Dist(this->GetActorLocation(), Target->GetActorLocation()) <= AttackRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacking!!"));
	}
}

void AAshMeleeEnemy::Damage(float Amount)
{
	FString ActorName = this->GetActorNameOrLabel();
	UE_LOG(LogTemp, Warning, TEXT("Enemy %s Take damage!"),*ActorName);
}

void AAshMeleeEnemy::Die()
{
	this->Destroy();
}

AActor* AAshMeleeEnemy::GetAggroTarget() const
{
	return AggroTarget.Get();
}

