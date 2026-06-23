// Fill out your copyright notice in the Description page of Project Settings.


#include "AshGroundSlam.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"

void UAshGroundSlam::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	TWeakObjectPtr<ACharacter> AvatarOwner = Cast<ACharacter>(ActorInfo->AvatarActor);
	if(!AvatarOwner.IsValid())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	//Prepare parameters for sphere trace BIGIN
	FVector CenterLocation = AvatarOwner->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	UClass* ActorClassFilter = ACharacter::StaticClass();

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(AvatarOwner.Get());

	TArray<AActor*> OverlappedActors;
	//Prepare parameters for sphere trace END

	bool bOverlap = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), 
											CenterLocation, 
											GroundSlamLaunchRadius,
											ObjectTypes, 
											ActorClassFilter, 
											IgnoredActors, 
											OverlappedActors);

	if (bOverlap)
	{
		for (AActor* Actor : OverlappedActors)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor))
			{
				FVector LaunchDirection = (Character->GetActorLocation() - AvatarOwner->GetActorLocation()).GetSafeNormal() * GroundSlamKnockbackSpeed + FVector(0, 0, GroundSlamKnockbackHeight);
				Character->LaunchCharacter(LaunchDirection, true, true);
			}
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UAshGroundSlam::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}