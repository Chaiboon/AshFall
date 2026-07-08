// Fill out your copyright notice in the Description page of Project Settings.


#include "AshGameState.h"

void AAshGameState::SetEnemyCount(int32 NewEnemyCount)
{
	EnemyCount = NewEnemyCount;
}

void AAshGameState::AddEnemyCount(int32 EnemyToAdd)
{
	SetEnemyCount(GetEnemyCount() + EnemyToAdd);
}
 
int32 AAshGameState::GetEnemyCount() const
{
	return EnemyCount;
}
