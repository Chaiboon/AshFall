// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlaySystem/AshPlayerState.h"

void AAshPlayerState::SetGold(int32 NewGold)
{
	Gold = NewGold;
}

void AAshPlayerState::AddGold(int32 Amount)
{
	SetGold(GetGold() + Amount);
}

int32 AAshPlayerState::GetGold() const
{
	return Gold;
}

void AAshPlayerState::SetExperience(int32 NewExperience)
{
	Experience = NewExperience;
}

void AAshPlayerState::AddExperience(int32 Amount)
{
	SetExperience(GetExperience() + Amount);
}

int32 AAshPlayerState::GetExperience() const
{
	return Experience;
}
