// Fill out your copyright notice in the Description page of Project Settings.


#include "AshBlockerAttributeSet.h"
#include "Enemies/AshShieldBlockerEnemy.h"

UAshBlockerAttributeSet::UAshBlockerAttributeSet()
{
	InitBlockHealth(200.0f);
	InitMaxBlockHealth(200.0f);
}

void UAshBlockerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	SetBlockHealth(FMath::Clamp(GetBlockHealth(), 0.0f, GetMaxBlockHealth()));

	if (GetBlockHealth() > 0) return;

	if (AAshShieldBlockerEnemy* Owner = Cast<AAshShieldBlockerEnemy>(this->GetOwningActor()))
	{
		Owner->bIsShieldBroke = true;
	}
}
