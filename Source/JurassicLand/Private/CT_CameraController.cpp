// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_CameraController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CT_PlayerController.h"



ACT_CameraController::ACT_CameraController()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-60, 0, 0));
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = false;
	

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCameraComponent"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
}

void ACT_CameraController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* CameraPlayercontroller = Cast<ACT_PlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CameraPlayercontroller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(imc, 0);
		}
	}
	
}

void ACT_CameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACT_CameraController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ia_Move, ETriggerEvent::Triggered, this, &ACT_CameraController::Move);
		EnhancedInputComponent->BindAction(ia_CameraOrbit, ETriggerEvent::Triggered, this, &ACT_CameraController::CameraOrbit);
		EnhancedInputComponent->BindAction(ia_CameraZoom, ETriggerEvent::Triggered, this, &ACT_CameraController::CameraZoom);
	}

}

void ACT_CameraController::Move(const FInputActionValue& value)
{
	FVector2D mValue = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, mValue.Y);
		AddMovementInput(RightDirection, mValue.X);
	}
	

}

void ACT_CameraController::CameraOrbit(const FInputActionValue& value)
{
	FVector2D lValue = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lValue.X * OrbitSpeed);
		//AddControllerPitchInput(lValue.Y * OrbitSpeed);
	}

}

void ACT_CameraController::CameraZoom(const FInputActionValue& value)
{
	FVector2D zValue = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + zValue.X * ZoomSpeed, 400.0f, 1000.0f);
	}

}

