// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AshBaseInstantDamageAbility.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AshCharacterInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "AshBaseCharacter.h"
#include "AshfallCharacter.h"

void UAshBaseInstantDamageAbility::OnHitEventReceived(FGameplayEventData Payload)
{
	AActor* Owner = GetAvatarActorFromActorInfo();
	if (!Owner) return;
	
	FVector CenterLocation = Owner->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	UClass* ActorClassFillter = ACharacter::StaticClass();
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Owner);

	TArray<AActor*> OverlappedActors;

	bool bOverlap = UKismetSystemLibrary::SphereOverlapActors(Owner->GetWorld(),
		CenterLocation, 
		GetAttackRange(),
		ObjectTypes,
		ActorClassFillter,
		IgnoredActors,
		OverlappedActors);

	if (!bOverlap) return;

	AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	if (!AbilitySystemComponent) return;
	for (AActor* Actor : OverlappedActors)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);
		
		if (!Character) continue;
		
		AController* OwnerController = Cast<ACharacter>(Owner)->GetController();
		if (!OwnerController) continue;
		
		AController* CharacterController = Character->GetController();
		if (!CharacterController) continue;

		FGenericTeamId OwnerTeam = Cast<IGenericTeamAgentInterface>(OwnerController)->GetGenericTeamId();
		if (!OwnerTeam) continue;

		FGenericTeamId TargetTeam = Cast<IGenericTeamAgentInterface>(CharacterController)->GetGenericTeamId();
		if (!TargetTeam) continue;

		if (FGenericTeamId::GetAttitude(OwnerTeam, TargetTeam) == ETeamAttitude::Friendly) continue;
			
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddInstigator(Owner,Owner);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, 1.0f, ContextHandle);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FGameplayTag::RequestGameplayTag("Data.Damage"), -GetDamageAmount());
		IAshCharacterInterface::Execute_Damage(Character, SpecHandle);
	}
}

FAshAbilityStatRow* UAshBaseInstantDamageAbility::GetAbilityData(FString AbilityName, int32 Level) const
{
	AAshBaseCharacter* Owner = Cast<AAshBaseCharacter>(GetAvatarActorFromActorInfo());
	if (!Owner) return nullptr;

	UDataTable* AbilityDataTable = Owner->AbilityStatsTable;
	if (!AbilityDataTable) return nullptr;

	FName AbilityToQuery = FName(*FString::Printf(TEXT("%s_%d"),*AbilityName, Level));
	FAshAbilityStatRow* AbilityRow = AbilityDataTable->FindRow<FAshAbilityStatRow>(AbilityToQuery, FString("Row not found"), true);
	if (!AbilityRow) return nullptr;
		
	return AbilityRow;
}
