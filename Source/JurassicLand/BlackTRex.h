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
	class USkeletalMeshComponent* TRexBody;
	class UCameraComponent* TRexEye;

	/*----Enhanced Input-------*/
private:
	UPROPERTY(VisibleAnywhere, Category =Input)
	class UInputMappingContext* IMC_TRex;

	UPROPERTY(VisibleAnywhere,Category = Input)
	class UInputAction* IA_Move;

	/*----Enhanced Input Function------*/
protected:
	void TRexMove(const FInputActionValue& Val);

	/*-----General Value----------*/
public:
	class APlayerController* pc;
};
