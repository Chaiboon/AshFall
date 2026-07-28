// Fill out your copyright notice in the Description page of Project Settings.


#include "AshShieldBlockerEnemy.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAshShieldBlockerEnemy::AAshShieldBlockerEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AttributeBlockerSet = CreateDefaultSubobject<UAshBlockerAttributeSet>(TEXT("BlockerAttributeSetComponent"));
}

// Called when the game starts or when spawned
void AAshShieldBlockerEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	if (!MoveComp) return;
	SetBaseWalkSpeed(MoveComp->MaxWalkSpeed);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(MovementImparingEffectClass, 1.0f, ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FGameplayTag::RequestGameplayTag("Data.SlowMove"), GetMovementSpeedDebuffMultiplier());
	SetSlowMovementEffectHandler(this->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()));
}

// Called every frame
void AAshShieldBlockerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAshShieldBlockerEnemy::IsAttackBlocked()
{
	bIsShieldBroke = this->AbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.NoShield")));
	if (bIsShieldBroke) return false;
	AActor* Attacker = IAshEnemyInterface::Execute_GetAggroTarget(this);
	if (!IsValid(Attacker)) return false;
	
	FVector AttackerLocation = Attacker->GetActorLocation();
	FVector BlockerLocation = this->GetActorLocation();
	FVector AgainstVector = (AttackerLocation - BlockerLocation).GetSafeNormal();

	FVector BlockerForwardVector = this->GetActorForwardVector();

	return BlockThreshold < FVector::DotProduct(BlockerForwardVector, AgainstVector);
}

float AAshShieldBlockerEnemy::GetMovementSpeedDebuffMultiplier()
{
	return MovementSpeedDebuffMultiplier;
}

float AAshShieldBlockerEnemy::GetBaseWalkSpeed()
{
	return BaseWalkSpeed;
}

void AAshShieldBlockerEnemy::SetBaseWalkSpeed(float NewBaseWalkSpeed)
{
	BaseWalkSpeed = NewBaseWalkSpeed;
}

FActiveGameplayEffectHandle AAshShieldBlockerEnemy::GetSlowMovementEffectHandler()
{
	return SlowMovementEffectHandler;
}

void AAshShieldBlockerEnemy::SetSlowMovementEffectHandler(FActiveGameplayEffectHandle NewSlowMovementEffectHandler)
{
	SlowMovementEffectHandler = NewSlowMovementEffectHandler;
}

void AAshShieldBlockerEnemy::Damage_Implementation(FGameplayEffectSpecHandle SpecHandle)
{

	FString ActorName = this->GetActorNameOrLabel();
	if (IsAttackBlocked())
	{
		UE_LOG(LogTemp, Warning, TEXT("Blocked"));
		float DamageAmount = SpecHandle.Data->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.Damage"));
		UE_LOG(LogTemp, Warning, TEXT("Damage %f"), DamageAmount);
		FGameplayEffectContextHandle ContextHandle = SpecHandle.Data->GetContext();
		FGameplayEffectSpecHandle BlockSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageBlockEffectClass, 1.0f, ContextHandle);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(BlockSpecHandle, FGameplayTag::RequestGameplayTag("Data.BlockDamage"), DamageAmount);
		Super::Damage_Implementation(BlockSpecHandle);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UnBlocked"));
		Super::Damage_Implementation(SpecHandle);
	}
}
