// Fill out your copyright notice in the Description page of Project Settings.


#include "AshMeleeEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "Enemies/AshMeleeAIController.h"


// Sets default values
AAshMeleeEnemy::AAshMeleeEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass = AAshMeleeAIController::StaticClass();
}

void AAshMeleeEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AAshMeleeAIController* ControllerWithTeam = Cast<AAshMeleeAIController>(NewController);
	if(ControllerWithTeam) ControllerWithTeam->SetGenericTeamId(TeamID);
}

// Called when the game starts or when spawned
void AAshMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();

	FGameplayAbilitySpec AbilitySpec(Ability, 1);
	AbilitySystemComponent->GiveAbility(AbilitySpec);
}