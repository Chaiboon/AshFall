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

void AAshShieldBlockerEnemy::Damage_Implementation(FGameplayEffectSpecHandle SpecHandle)
{

	FString ActorName = this->GetActorNameOrLabel();
	if (IsAttackBlocked())
	{
		float DamageAmount = SpecHandle.Data->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.Damage"));
		FGameplayEffectContextHandle ContextHandle = SpecHandle.Data->GetContext();

		FGameplayEffectSpecHandle BlockSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageBlockEffectClass, 1.0f, ContextHandle);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(BlockSpecHandle, FGameplayTag::RequestGameplayTag("Data.BlockDamage"), -DamageAmount);
		Super::Damage_Implementation(BlockSpecHandle);
	}
	else
	{
		Super::Damage_Implementation(SpecHandle);
	}
}
