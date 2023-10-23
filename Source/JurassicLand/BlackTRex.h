// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "BlackTRex.generated.h"

UCLASS()
class JURASSICLAND_API ABlackTRex : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlackTRex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	
	/*-----Character Component-----*/
public:
	UPROPERTY(EditAnywhere, Category= CharacterSettings)
	class USkeletalMeshComponent* TRexBody;
	UPROPERTY(EditAnywhere, Category= CharacterSettings)
	class UCameraComponent* TRexEye;

	/*----Enhanced Input set up Value-------*/
private:
	UPROPERTY(VisibleAnywhere, Category =Input)
	class UInputMappingContext* IMC_TRex;

	UPROPERTY(EditAnywhere, Category = Input)
	TArray<class UInputAction*> InputActions;

	/*----Enhanced Input Function------*/
protected:
	void SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputActions );
	
	void TRexMove(const FInputActionValue& Val);
	/*-----General Value----------*/
public:
	class APlayerController* pc;
};
