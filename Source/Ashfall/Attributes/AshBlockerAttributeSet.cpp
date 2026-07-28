// Fill out your copyright notice in the Description page of Project Settings.


#include "AshBlockerAttributeSet.h"
#include "Enemies/AshShieldBlockerEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

UAshBlockerAttributeSet::UAshBlockerAttributeSet()
{
	InitBlockHealth(200.0f);
	InitMaxBlockHealth(200.0f);
	InitMoveSpeedMultiplier(1.0f);
}

void UAshBlockerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	SetBlockHealth(FMath::Clamp(GetBlockHealth(), 0.0f, GetMaxBlockHealth()));

	if (GetBlockHealth() > 0) return;

	if (AAshShieldBlockerEnemy* Owner = Cast<AAshShieldBlockerEnemy>(this->GetOwningActor()))
	{
		Owner->AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.NoShield"));
		
		FActiveGameplayEffectHandle Handler = Owner->GetSlowMovementEffectHandler();
		Owner->AbilitySystemComponent->RemoveActiveGameplayEffect(Handler,-1);
	}
}

void UAshBlockerAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute != GetMoveSpeedMultiplierAttribute()) return;

	AAshShieldBlockerEnemy* Owner = Cast<AAshShieldBlockerEnemy>(this->GetOwningActor());
	if (!Owner) return;

	UCharacterMovementComponent* MoveComp = Owner->GetCharacterMovement();
	if (!MoveComp) return;

	MoveComp->MaxWalkSpeed = Owner->GetBaseWalkSpeed() * NewValue;
}
