// Fill out your copyright notice in the Description page of Project Settings.


#include "AshLightAttackNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Enemies/AshEnemyInterface.h"

void UAshLightAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{	
	if (AActor* Owner = MeshComp->GetOwner())
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
																	LightAttackRange,
																	ObjectTypes,
																	ActorClassFillter,
																	IgnoredActors,
																	OverlappedActors);

		if (!bOverlap) return;
		for (AActor* Actor : OverlappedActors)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor))
			{
				if (Character->Implements<UAshEnemyInterface>())
				{

					IAshEnemyInterface::Execute_Damage(Character,DamageAmount);
				}
			}
		}
	}
}