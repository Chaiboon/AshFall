// Fill out your copyright notice in the Description page of Project Settings.


#include "AshCheckAttackNotify.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AshCombatAttackerInterface.h"
#include "AshfallCharacter.h"

void UAshCheckAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = Cast<AActor>(MeshComp->GetOwner());
	if (!Owner || !Owner->Implements<UAshCombatAttackerInterface>()) return;


	IAshCombatAttackerInterface::Execute_CheckAttack(Owner,AbilityTag);	
}
