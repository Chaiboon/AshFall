// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Attributes/AshAttributeSet.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Engine/DataTable.h"
#include "AshBaseCharacter.h"
#include "GenericTeamAgentInterface.h"

#include "AshfallCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;


UENUM(BlueprintType)
enum class EAshAbilityInputID : uint8
{
	None			= 0		UMETA(DisplayName = "Other Ability"),
	ChargeAttack	= 1		UMETA(DisplayName = "Charge Attack")
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AAshfallCharacter :	public AAshBaseCharacter
							
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LightAttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* DodgeRollAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* GroundSlamAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ChargeAttackAction;

public:

	/** Constructor */
	AAshfallCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void LightAttack(const FInputActionValue& Value);
	void DodgeRoll(const FInputActionValue& Value);
	void GroundSlam(const FInputActionValue& Value);
	void ChargeAttack(const FInputActionValue& Value);
	void OnHoldAbilityEnd(const FInputActionValue& Value);
public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category="Ability")
	TSubclassOf<UGameplayAbility> LightAttackAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> DodgeRollAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> GroundSlamAbilityClass;
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> ChargeAttactAbilityClass;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	FGameplayTag LightAttackTag;
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	FGameplayTag ChargeAttackTag;
	UPROPERTY(EditDefaultsOnly)
	FGenericTeamId TeamID = 1;
	virtual void PossessedBy(AController* NewController) override;
};
 