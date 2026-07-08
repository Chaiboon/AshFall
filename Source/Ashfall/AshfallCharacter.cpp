// Copyright Epic Games, Inc. All Rights Reserved.

#include "AshfallCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Abilities/AshLightAttack.h"
#include "Abilities/AshDodgeRoll.h"
#include "AbilitySystemComponent.h"
#include "Abilities/AshChargeAttackAbility.h"
#include "Ashfall.h"
#include "Enemies/AshBaseEnemy.h"
#include "AbilitySystemBlueprintLibrary.h"


AAshfallCharacter::AAshfallCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAshAttributeSet>(TEXT("AttributeSetComponent"));
}

void AAshfallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAshfallCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AAshfallCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAshfallCharacter::Look);

		// Attacking
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &AAshfallCharacter::LightAttack);

		// Dodging
		EnhancedInputComponent->BindAction(DodgeRollAction, ETriggerEvent::Started, this, &AAshfallCharacter::DodgeRoll);

		// Ground Slamming
		EnhancedInputComponent->BindAction(GroundSlamAction, ETriggerEvent::Started, this, &AAshfallCharacter::GroundSlam);
		
		// Charge Attacking
		EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Started, this, &AAshfallCharacter::ChargeAttack);
		EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Completed, this, &AAshfallCharacter::OnHoldAbilityEnd);
		EnhancedInputComponent->BindAction(ChargeAttackAction, ETriggerEvent::Canceled, this, &AAshfallCharacter::OnHoldAbilityEnd);
	}
	else
	{
		UE_LOG(LogAshfall, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAshfallCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AAshfallCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AAshfallCharacter::LightAttack(const FInputActionValue& Value)
{
	if (!IsValid(AbilitySystemComponent) || !LightAttackAbilityClass) return;
	AbilitySystemComponent->TryActivateAbilityByClass(LightAttackAbilityClass);
}

void AAshfallCharacter::DodgeRoll(const FInputActionValue& Value)
{
	if (!IsValid(AbilitySystemComponent) || !DodgeRollAbilityClass) return;
	AbilitySystemComponent->TryActivateAbilityByClass(DodgeRollAbilityClass);
}

void AAshfallCharacter::GroundSlam(const FInputActionValue& Value)
{
	if (!IsValid(AbilitySystemComponent) || !GroundSlamAbilityClass) return;
	AbilitySystemComponent->TryActivateAbilityByClass(GroundSlamAbilityClass);
}

void AAshfallCharacter::ChargeAttack(const FInputActionValue& Value)
{
	if (!IsValid(AbilitySystemComponent) || !ChargeAttactAbilityClass) return;
	
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAshAbilityInputID::ChargeAttack));

	UE_LOG(LogTemp, Warning, TEXT("Press button"));
}

void AAshfallCharacter::OnHoldAbilityEnd(const FInputActionValue& Value)
{
	if (!IsValid(AbilitySystemComponent) || !ChargeAttactAbilityClass) return;
	
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(EAshAbilityInputID::ChargeAttack));
	UE_LOG(LogTemp, Warning, TEXT("Released button"));
	
}

void AAshfallCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AAshfallCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AAshfallCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AAshfallCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AAshfallCharacter::BeginPlay()
{
	Super::BeginPlay();

	FGameplayAbilitySpec LightAttackSpec(LightAttackAbilityClass, 1);
	FGameplayAbilitySpec DodgeRollSpec(DodgeRollAbilityClass, 1);
	FGameplayAbilitySpec GroundSlamSpec(GroundSlamAbilityClass, 1);
	FGameplayAbilitySpec ChargeAttaclSpec(ChargeAttactAbilityClass, 1, static_cast<int32>(EAshAbilityInputID::ChargeAttack));

	AbilitySystemComponent->GiveAbility(LightAttackSpec);
	AbilitySystemComponent->GiveAbility(DodgeRollSpec);
	AbilitySystemComponent->GiveAbility(GroundSlamSpec);
	AbilitySystemComponent->GiveAbility(ChargeAttaclSpec);
}

UAbilitySystemComponent* AAshfallCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAshAttributeSet* AAshfallCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AAshfallCharacter::CheckChargedAttack_Implementation()
{
	FGameplayEventData Payload;
	Payload.Instigator = this;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,
		FGameplayTag::RequestGameplayTag(TEXT("Event.ChargeAttack.Hit")),
		Payload);
}

void AAshfallCharacter::CheckLightAttack_Implementation()
{
	FGameplayEventData Payload;
	Payload.Instigator = this;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,
		FGameplayTag::RequestGameplayTag(TEXT("Event.LightAttack.Hit")),
		Payload);
}

void AAshfallCharacter::Damage_Implementation(FGameplayEffectSpecHandle SpecHandle)
{
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AAshfallCharacter::Die_Implementation()
{
	this->Destroy();
}
