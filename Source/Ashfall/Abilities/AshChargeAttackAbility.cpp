// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AshChargeAttackAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UAshChargeAttackAbility::UAshChargeAttackAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UAshChargeAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	ChargeStartTime = GetWorld()->GetTimeSeconds();

	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		ChargeAnimMontageToPlay,
		1.0f,
		NAME_None,
		true,
		1.0f
	);

	if (PlayMontageTask)
	{
		PlayMontageTask->OnCompleted.AddDynamic(this, &UAshChargeAttackAbility::OnChargeMontageCompleted);
		PlayMontageTask->OnCancelled.AddDynamic(this, &UAshChargeAttackAbility::OnChargeMontageCancelled);
		PlayMontageTask->OnInterrupted.AddDynamic(this, &UAshChargeAttackAbility::OnChargeMontageCancelled);

		PlayMontageTask->ReadyForActivation();
	}
	else 
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("Charge begins"));
	

	if (UAbilityTask_WaitInputRelease* WaitReleaseTask = UAbilityTask_WaitInputRelease::WaitInputRelease(this))
	{
		WaitReleaseTask->OnRelease.AddDynamic(this, &UAshChargeAttackAbility::OnRelease);

		WaitReleaseTask->ReadyForActivation();
	}
}

void UAshChargeAttackAbility::OnRelease(float TimeHeld)
{
	
	float ActualTimeCharged = GetWorld()->GetTimeSeconds() - ChargeStartTime;
	ChargePercent = FMath::Clamp(ActualTimeCharged / MaxChargeTime, 0.0f, 1.0f);


	if (ActualTimeCharged >= MinChargeTime)
	{
		UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			ReleaseAnimMontageToPlay,
			1.0f,
			NAME_None,
			true,
			1.0f
		);

		if (PlayMontageTask) 
		{
			PlayMontageTask->OnCompleted.AddDynamic(this, &UAshChargeAttackAbility::OnReleaseMontageCompleted);
			PlayMontageTask->OnCancelled.AddDynamic(this, &UAshChargeAttackAbility::OnReleaseeMontageCancelled);
			PlayMontageTask->OnInterrupted.AddDynamic(this, &UAshChargeAttackAbility::OnReleaseeMontageCancelled);

			PlayMontageTask->ReadyForActivation();
		}

		if (UAbilityTask_WaitGameplayEvent* WaitReleaseEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Event.ChargeAttack.Hit"))))
		{
			WaitReleaseEvent->EventReceived.AddDynamic(this, &UAshChargeAttackAbility::OnEventReceived);

			WaitReleaseEvent->ReadyForActivation();
		}

	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}


}

void UAshChargeAttackAbility::OnChargeMontageCompleted()
{

}

void UAshChargeAttackAbility::OnChargeMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UAshChargeAttackAbility::OnReleaseMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UAshChargeAttackAbility::OnReleaseeMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UAshChargeAttackAbility::OnEventReceived(FGameplayEventData Payload)
{
}
