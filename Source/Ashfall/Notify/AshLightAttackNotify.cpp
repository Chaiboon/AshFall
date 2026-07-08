// Fill out your copyright notice in the Description page of Project Settings.


#include "AshLightAttackNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "AshCombatAttackerInterface.h"
#include "AshfallCharacter.h"

void UAshLightAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{	
	if (AActor* Owner = Cast<AActor>(MeshComp->GetOwner()))
	{
		if (Owner->Implements<UAshCombatAttackerInterface>())
		{
			IAshCombatAttackerInterface::Execute_CheckLightAttack(Owner);
		}
	}
}