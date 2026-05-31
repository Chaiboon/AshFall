// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AshAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASHFALL_API UAshAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	float Speed;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
