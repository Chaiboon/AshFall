// Fill out your copyright notice in the Description page of Project Settings.


#include "AshBaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAshBaseEnemy::AAshBaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAshEnemyAttributeSet>(TEXT("AttributeSetComponent"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AAshBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	AggroTarget = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

// Called every frame
void AAshBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAshBaseEnemy::Damage_Implementation(float Amount)
{
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, 1.0f,AbilitySystemComponent->MakeEffectContext());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,FGameplayTag::RequestGameplayTag("Data.Damage"),-Amount);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AAshBaseEnemy::Die_Implementation()
{
	this->Destroy();
}

AActor* AAshBaseEnemy::GetAggroTarget_Implementation() const
{
	return AggroTarget.Get();
}

UAbilitySystemComponent* AAshBaseEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAshEnemyAttributeSet* AAshBaseEnemy::GetAttributeSet() const
{
	return AttributeSet;
}