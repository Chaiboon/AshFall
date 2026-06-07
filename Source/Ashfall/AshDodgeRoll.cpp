// Fill out your copyright notice in the Description page of Project Settings.


#include "AshDodgeRoll.h"
#include "GameFramework/Character.h"
#include "AshfallCharacter.h"

void UAshDodgeRoll::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
								const FGameplayAbilityActorInfo* ActorInfo, 
								const FGameplayAbilityActivationInfo ActivationInfo, 
								const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true,true);
		return;
	}

	TWeakObjectPtr<ACharacter> AvatarOwner = Cast<ACharacter>(ActorInfo->AvatarActor);
	if (!AvatarOwner.IsValid())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}
	
	FVector LaunchDirection = AvatarOwner->GetActorForwardVector() * DodgeRollLaunchStrength + FVector(0, 0, DodgeRollLaunchZAxis);
	
	AshfallCharacter = Cast<AAshfallCharacter>(AvatarOwner.Get());
	AvatarOwner.Get()->LaunchCharacter(LaunchDirection, true, true);

	if (AshfallCharacter)
	{
		AshfallCharacter->AbilitySystemComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.DodgeRolling"));

		GetWorld()->GetTimerManager().SetTimer(
			InvincibilityTimer,
			this,
			&UAshDodgeRoll::OnInvicibilityEnd,          
			InvincibilityDuration,          
			false);
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	
	
}

void UAshDodgeRoll::EndAbility(const FGameplayAbilitySpecHandle Handle, 
							const FGameplayAbilityActorInfo* ActorInfo, 
							const FGameplayAbilityActivationInfo ActivationInfo, 
							bool bReplicateEndAbility, 
							bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAshDodgeRoll::OnInvicibilityEnd()
{
	if(IsValid(AshfallCharacter)) AshfallCharacter->AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.DodgeRolling"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
