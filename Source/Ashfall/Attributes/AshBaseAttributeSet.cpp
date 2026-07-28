// Fill out your copyright notice in the Description page of Project Settings.


#include "AshBaseAttributeSet.h"
#include "AshBaseCharacter.h"
#include "AshCharacterInterface.h"

UAshBaseAttributeSet::UAshBaseAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UAshBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

	if (GetHealth() > 0) return;

	if (AAshBaseCharacter* Owner = Cast<AAshBaseCharacter>(this->GetOwningActor()))
	{
		IAshCharacterInterface::Execute_Die(Owner);
	}
}
