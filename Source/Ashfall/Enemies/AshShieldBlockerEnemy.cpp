// Fill out your copyright notice in the Description page of Project Settings.


#include "AshShieldBlockerEnemy.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAshShieldBlockerEnemy::AAshShieldBlockerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeBlockerSet = CreateDefaultSubobject<UAshBlockerAttributeSet>(TEXT("BlockerAttributeSetComponent"));
}

// Called when the game starts or when spawned
void AAshShieldBlockerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAshShieldBlockerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAshShieldBlockerEnemy::IsAttackBlocked()
{
	if (bIsShieldBroke) return false;
	AActor* Attacker = IAshEnemyInterface::Execute_GetAggroTarget(this);
	if (!IsValid(Attacker)) return false;
	
	FVector AttackerLocation = Attacker->GetActorLocation();
	FVector BlockerLocation = this->GetActorLocation();
	FVector AgainstVector = (AttackerLocation - BlockerLocation).GetSafeNormal();

	FVector BlockerForwardVector = this->GetActorForwardVector();

	return BlockThreshold < FVector::DotProduct(BlockerForwardVector, AgainstVector);
}

void AAshShieldBlockerEnemy::Damage_Implementation(float Amount)
{

	FString ActorName = this->GetActorNameOrLabel();
	if (IsAttackBlocked())
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageBlockEffectClass, 1.0f, AbilitySystemComponent->MakeEffectContext());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FGameplayTag::RequestGameplayTag("Data.BlockDamage"), -Amount);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	else
	{
		Super::Damage_Implementation(Amount);
	}
}
