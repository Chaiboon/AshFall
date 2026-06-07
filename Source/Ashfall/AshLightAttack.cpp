// Fill out your copyright notice in the Description page of Project Settings.


#include "AshLightAttack.h"

void UAshLightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
										const FGameplayAbilityActorInfo* ActorInfo, 
										const FGameplayAbilityActivationInfo ActivationInfo, 
										const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo)) {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Light attack ability activated"));
}

void UAshLightAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, 
									const FGameplayAbilityActorInfo* ActorInfo, 
									const FGameplayAbilityActivationInfo ActivationInfo, 
									bool bReplicateEndAbility, 
									bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
