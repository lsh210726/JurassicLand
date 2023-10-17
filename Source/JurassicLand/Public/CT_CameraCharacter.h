// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CT_CameraCharacter.generated.h"

UCLASS()
class JURASSICLAND_API ACT_CameraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACT_CameraCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class APlayerController* CameraPlayercontroller;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* imc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_CameraOrbit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_CameraZoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_CameraPitch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_MouseMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_MouseRightClick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ia_MouseLeftClick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float OrbitSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float ZoomSpeed = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float ZoomMin = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float ZoomMax = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float InitialMovementSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float CameraMinClamp = -70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float CameraMaxClamp = -20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	bool bRightButtonPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create")
	bool bPlacementModeEnable = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create")
	class AActor* PlaceableActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Create")
	class UCT_CreateComponent* createComp;


public:
	
	void Move(const FInputActionValue& value);
	void CameraOrbit(const FInputActionValue& value);
	void CameraZoom(const FInputActionValue& value);
	void CameraPitch(const FInputActionValue& value);
	void MouseMove(const FInputActionValue& value);
	void StartMouseRightClick();
	void EndMouseRightClick();
	void UpdateMovementSpeed();
	void SetPlacementmoveEnabled(bool bIsEnabled);
	void UpdatePlacement();
	void SpawnBuilding();
	void MouseLeftClick();
	





};
