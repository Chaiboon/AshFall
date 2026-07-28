// Fill out your copyright notice in the Description page of Project Settings.


#include "AshGameMode.h"
#include "AshGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlaySystem/AshPlayerState.h"
#include "GameFramework/PlayerStart.h"

namespace MatchState
{
	const FName ArenaCleared = FName(TEXT("ArenaCleared"));
	const FName SaveRoom = FName(TEXT("SaveRoom"));
}

AAshGameMode::AAshGameMode()
{
	PlayerStateClass = AAshPlayerState::StaticClass();
}
void AAshGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AAshGameMode::OnEnemyDied()
{
	AAshGameState* CurrentGameState = GetWorld()->GetGameState<AAshGameState>();

	if (!CurrentGameState) return;

	CurrentGameState->SetEnemyCount(CurrentGameState->GetEnemyCount() - 1);

	if (CurrentGameState->GetEnemyCount() > 0) return;

	CurrentGameState->OnArenaCleared.Broadcast();
	SetMatchState(MatchState::ArenaCleared);
}

void AAshGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	if (MatchState == MatchState::ArenaCleared)
	{
		UE_LOG(LogTemp, Warning, TEXT("Arena cleared"));
	}
}

AActor* AAshGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> StartingPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartingPoints);

	if (!StartingPoints.Num()) return Super::ChoosePlayerStart_Implementation(Player);

	for (AActor* StartingPoint : StartingPoints)
	{
		APlayerStart* Point = Cast<APlayerStart>(StartingPoint);
		if (!Point) continue;
		if(Point->PlayerStartTag == TargetPlayerStartTag) return StartingPoint;
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}


