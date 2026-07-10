// Fill out your copyright notice in the Description page of Project Settings.


#include "AshBaseCharacter.h"

// Sets default values
AAshBaseCharacter::AAshBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAshBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AAshBaseCharacter::Tick(float DeltaTime)
{
}

// Called to bind functionality to input
void AAshBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AAshBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAshBaseAttributeSet* AAshBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}
