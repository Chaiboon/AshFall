// Fill out your copyright notice in the Description page of Project Settings.


#include "AshChargeAttackNotify.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AshCombatAttackerInterface.h"
#include "AshfallCharacter.h"

void UAshChargeAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Owner = Cast<AActor>(MeshComp->GetOwner()))
	{
		if (Owner->Implements<UAshCombatAttackerInterface>())
		{
			IAshCombatAttackerInterface::Execute_CheckChargedAttack(Owner);
		}
	}
}
