// Fill out your copyright notice in the Description page of Project Settings.


#include "AshLightAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework/Character.h"

void UAshLightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
										const FGameplayAbilityActorInfo* ActorInfo, 
										const FGameplayAbilityActivationInfo ActivationInfo, 
										const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo) || !AnimMontageToPlay) {
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		AnimMontageToPlay,
		1.0f,         
		NAME_None,     
		true,         
		1.0f           
	);

	if (PlayMontageTask)
	{
		PlayMontageTask->OnCompleted.AddDynamic(this, &UAshLightAttack::OnMontageCompleted);
		PlayMontageTask->OnCancelled.AddDynamic(this, &UAshLightAttack::OnMontageCancelled);
		PlayMontageTask->OnInterrupted.AddDynamic(this, &UAshLightAttack::OnMontageCancelled);
		
		PlayMontageTask->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	if(UAbilityTask_WaitGameplayEvent* WaitHitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Event.LightAttack.Hit"))))
	{
		WaitHitEvent->EventReceived.AddDynamic(this, &UAshLightAttack::OnHitEventReceived);
		WaitHitEvent->ReadyForActivation();
	}

}

void UAshLightAttack::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
void UAshLightAttack::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

float UAshLightAttack::GetDamageAmount() const
{
	if (FAshAbilityStatRow* AbilityRow = GetAbilityData(FString("LightAttack"), 1))
	{
		return AbilityRow->Damage;
	}
	return 0.0f;
}

float UAshLightAttack::GetAttackRange() const
{
	if (FAshAbilityStatRow* AbilityRow = GetAbilityData(FString("LightAttack"), 1))
	{
		return AbilityRow->AttackRange;
	}
	return 0.0f;
}
