// Fill out your copyright notice in the Description page of Project Settings.


#include "AshAnimInstance.h"

void UAshAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (APawn* OwnerPawn = TryGetPawnOwner())
	{
		Speed = OwnerPawn->GetVelocity().Size();
	}
}
