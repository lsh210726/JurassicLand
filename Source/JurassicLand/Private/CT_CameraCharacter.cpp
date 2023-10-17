// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_CameraCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CT_PlayerController.h"
#include "CT_ClickableComponent.h"
#include "CT_CreateComponent.h"
#include "CreateObject.h"



ACT_CameraCharacter::ACT_CameraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-60, 0, 0));
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bUsePawnControlRotation = false;	

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCameraComponent"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	createComp = CreateDefaultSubobject<UCT_CreateComponent>(TEXT("CreateComponent"));
}


void ACT_CameraCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraPlayercontroller = Cast<ACT_PlayerController>(Controller);

	if (CameraPlayercontroller)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CameraPlayercontroller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(imc, 0);
		}
	}
	
	InitialMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;

	UpdateMovementSpeed();

	SetPlacementmoveEnabled(true);
}

void ACT_CameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bPlacementModeEnable) UpdatePlacement();

}

void ACT_CameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ia_Move, ETriggerEvent::Triggered, this, &ACT_CameraCharacter::Move);
		EnhancedInputComponent->BindAction(ia_CameraOrbit, ETriggerEvent::Triggered, this, &ACT_CameraCharacter::CameraOrbit);
		EnhancedInputComponent->BindAction(ia_CameraZoom, ETriggerEvent::Triggered, this, &ACT_CameraCharacter::CameraZoom);
		EnhancedInputComponent->BindAction(ia_CameraPitch, ETriggerEvent::Triggered, this, &ACT_CameraCharacter::CameraPitch);
		EnhancedInputComponent->BindAction(ia_MouseMove, ETriggerEvent::Triggered, this, &ACT_CameraCharacter::MouseMove);
		EnhancedInputComponent->BindAction(ia_MouseRightClick, ETriggerEvent::Started, this, &ACT_CameraCharacter::StartMouseRightClick);
		EnhancedInputComponent->BindAction(ia_MouseRightClick, ETriggerEvent::Completed, this, &ACT_CameraCharacter::EndMouseRightClick);
		EnhancedInputComponent->BindAction(ia_MouseLeftClick, ETriggerEvent::Started, this, &ACT_CameraCharacter::MouseLeftClick);
	}

}

void ACT_CameraCharacter::Move(const FInputActionValue& value)
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

void ACT_CameraCharacter::CameraOrbit(const FInputActionValue& value)
{
	FVector2D lValue = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(lValue.X * OrbitSpeed);
	}
}

void ACT_CameraCharacter::CameraZoom(const FInputActionValue& value)
{
	FVector2D zValue = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength + zValue.X * ZoomSpeed, ZoomMin, ZoomMax);
		UpdateMovementSpeed();
	}

}

void ACT_CameraCharacter::CameraPitch(const FInputActionValue& value)
{
	float pValue = value.Get<float>();

	FRotator CameraBoomRot = CameraBoom->GetRelativeRotation();
	float currPitch = FMath::ClampAngle(CameraBoomRot.Pitch + (OrbitSpeed * pValue), CameraMinClamp, CameraMaxClamp);
	FRotator CameraBoomPitchRot(currPitch, 0, 0);

	CameraBoom->SetRelativeRotation(CameraBoomPitchRot);

}

void ACT_CameraCharacter::MouseMove(const FInputActionValue& value)
{
	FVector2D mouseValue = value.Get<FVector2D>();

	if (bRightButtonPressed)
	{
		CameraOrbit(value);
		CameraPitch(value);
	}
}

void ACT_CameraCharacter::StartMouseRightClick()
{
	bRightButtonPressed = true;
}

void ACT_CameraCharacter::EndMouseRightClick()
{
	bRightButtonPressed = false;
}

void ACT_CameraCharacter::UpdateMovementSpeed()
{
	float currentWalkSpeed = InitialMovementSpeed * (CameraBoom->TargetArmLength / ZoomMin);

	GetCharacterMovement()->MaxWalkSpeed = currentWalkSpeed;
}

void ACT_CameraCharacter::SetPlacementmoveEnabled(bool bIsEnabled)
{
	if (bIsEnabled != bPlacementModeEnable)
	{
		bPlacementModeEnable = bIsEnabled;

		if (!bPlacementModeEnable)
		{
			if (IsValid(PlaceableActor))
			{
				PlaceableActor->Destroy();
			}
		}
		else
		{
			PlaceableActor = GetWorld()->SpawnActor<ACreateObject>(ACreateObject::StaticClass(), FVector(0, 0, -1000000), FRotator::ZeroRotator);
			UCT_ClickableComponent* ClickableComp = PlaceableActor->GetComponentByClass<UCT_ClickableComponent>();

			if (IsValid(ClickableComp))
			{
				ClickableComp->InPlacementMode();
			}
			else
			{
				PlaceableActor->AddInstanceComponent(createComp);
			}
		}
	}
}

void ACT_CameraCharacter::UpdatePlacement()
{
	FVector mouseLoc, mouseDir;
	CameraPlayercontroller->DeprojectMousePositionToWorld(mouseLoc, mouseDir);
	//DrawDebugLine(GetWorld(), mouseLoc, mouseLoc + mouseDir * 100.0f, FColor::Red, true);

	FHitResult hitInfo;
	FCollisionQueryParams params;

	if(GetWorld()->LineTraceSingleByChannel(hitInfo, mouseLoc, mouseLoc + mouseDir * 10000.0f, ECollisionChannel::ECC_GameTraceChannel1, params))
	{
		if (hitInfo.bBlockingHit)
		{
			PlaceableActor->SetActorLocation(FVector(hitInfo.Location));
		}
	}

	SetPlacementmoveEnabled(true);
}

void ACT_CameraCharacter::SpawnBuilding()
{
	UCT_CreateComponent* tmpCreateComp = PlaceableActor->GetComponentByClass<UCT_CreateComponent>();
	if (IsValid(tmpCreateComp))
	{
		if (tmpCreateComp->bIsPlacementValid)
		{
			FTransform spawnTrans = PlaceableActor->GetActorTransform();
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GetWorld()->SpawnActor<ACreateObject>(ACreateObject::StaticClass(), spawnTrans, SpawnParams);
		}
		else
		{
			FString ValueString = tmpCreateComp->bIsPlacementValid ? TEXT("bIsPlacementValid : True") : TEXT("bIsPlacementValid : False");
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ValueString);
		}
	}
	else
	{
		FString ValueString = IsValid(tmpCreateComp) ? TEXT("Valid") : TEXT("bIsPlacementValid : False");
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ValueString);
	}
}

void ACT_CameraCharacter::MouseLeftClick()
{
	FString ValueString = bPlacementModeEnable ? TEXT("True") : TEXT("False");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ValueString);

	if(bPlacementModeEnable) SpawnBuilding();	
}

