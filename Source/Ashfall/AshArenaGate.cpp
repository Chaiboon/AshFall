// Fill out your copyright notice in the Description page of Project Settings.


#include "AshArenaGate.h"

// Sets default values
AAshArenaGate::AAshArenaGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAshArenaGate::BeginPlay()
{
	Super::BeginPlay();
	
	GameState = GetWorld()->GetGameState<AAshGameState>();
	if (!GameState) return;
	GameState->OnArenaCleared.AddDynamic(this,&AAshArenaGate::OpenAreaGate);
}

void AAshArenaGate::OpenAreaGate()
{
	UE_LOG(LogTemp, Warning, TEXT("Gate Open"));
}


