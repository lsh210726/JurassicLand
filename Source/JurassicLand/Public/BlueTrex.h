// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "BlueTrex.generated.h"

UCLASS()
class JURASSICLAND_API ABlueTrex : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlueTrex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*-----Enhanced Input Value-----*/
	
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* IMC_TRex;
	UPROPERTY(EditAnywhere, Category = Input)
	TArray<class UInputAction*> inputActions;


	/*------ Enhanced Input Function -----*/
	void SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions);

	void TRexMove(const FInputActionValue& Val);
	void TRexLook(const FInputActionValue& Val);
	UFUNCTION(BlueprintNativeEvent)
	//UFUNCTION()
	void TRexTailAttack(const FInputActionValue& Val);
	//UPROPERTY(BlueprintReadWrite,BlueprintAssignable)
	//tailATK

	/*----- Character Component-----*/
public:
	UPROPERTY(EditAnywhere, Category= CharacterSettings, BlueprintReadWrite)
	class USkeletalMeshComponent* TRexBody;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= CharacterSettings)
	class UCameraComponent* TRexEye;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= CharacterSettings)
	class USpringArmComponent* TRexEyeArm;

	/*----- Damage System Value --------*/
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP동기화
	float TRexHP = 50;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;//변수 동기화 위한 함수

	float TRexPower = 12;

	// hp - 지은
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP동기화
	bool bIsHpZero = false;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsHPShow = false;

	/*----- General Value ----------*/
public:
	class APlayerController* pc;
	class UCharacterMovementComponent* CharacterMovement;

	/*-------- Animation Value --------*/

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Anim)
 	bool TailAttack = false;

private:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
    class UAnimationAsset* TailAttackAnim;

public:
	// 닉네임 ui component
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UJE_NicknameComponent* nickComp;*/

	// 닉네임 textrender
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Nickname")
	class UTextRenderComponent* nicknameText;

	class ULSH_NetGameInstance* gi;

public:
	//코인
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float initialCoin = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float currentCoin = 0.0f;

	
};
 