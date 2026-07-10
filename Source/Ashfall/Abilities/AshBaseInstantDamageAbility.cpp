// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AshBaseInstantDamageAbility.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemies/AshEnemyInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AshBaseCharacter.h"
#include "AshfallCharacter.h"

void UAshBaseInstantDamageAbility::OnHitEventReceived(FGameplayEventData Payload)
{
	if (AActor* Owner = GetAvatarActorFromActorInfo())
	{
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
			if (ACharacter* Character = Cast<ACharacter>(Actor))
			{
				if (Character->Implements<UAshEnemyInterface>() || Character->Implements<UAshPlayerInterface>())
				{
					FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
					ContextHandle.AddInstigator(Owner,Owner);

					FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffectClass, 1.0f, ContextHandle);
					UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FGameplayTag::RequestGameplayTag("Data.Damage"), -GetDamageAmount());
					if (Character->Implements<UAshEnemyInterface>()) IAshEnemyInterface::Execute_Damage(Character, SpecHandle); else IAshPlayerInterface::Execute_Damage(Character, SpecHandle);
				}
			}
		}
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
