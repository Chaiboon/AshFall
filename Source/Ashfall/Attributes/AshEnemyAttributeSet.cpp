// Fill out your copyright notice in the Description page of Project Settings.


#include "AshEnemyAttributeSet.h"
#include "Enemies/AshBaseEnemy.h"

UAshEnemyAttributeSet::UAshEnemyAttributeSet()
	:UAshBaseAttributeSet()
{
	
}

void UAshEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	if (GetHealth() > 0) return;

	if (AAshBaseEnemy* Owner = Cast<AAshBaseEnemy>(this->GetOwningActor()))
	{
		if (Owner->GetClass()->ImplementsInterface(UAshEnemyInterface::StaticClass()))
		{
			IAshEnemyInterface::Execute_Die(Owner);
		}
	}
}
