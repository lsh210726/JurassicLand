// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "JE_CustomItemData.h"
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
	// hp - 지은
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")//HP동기화
	bool bIsHpZero = false;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsHPShow = false;

	bool btickStop = false;

	// 지은
public:
	// 닉네임 ui component
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UJE_NicknameComponent* nickComp;*/

	// 닉네임 변수
	UPROPERTY(Replicated)
	FString playerName = "Dinosaur";

	// 닉네임 textrender
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Nickname")
	class UTextRenderComponent* nicknameText;

	class ULSH_NetGameInstance* gi;

/*---------------------------- 지은 ----------------------------*/
//코인
public:
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float initialCoin = 500.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float currentCoin = 0.0f;

//커스텀
public:
	class UMaterialInstanceDynamic* dynamicMat1;
	// 색 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FLinearColor playerColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	bool IsColor = false;

	// 메쉬 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	int32 playerMeshNumber = 0;

public:
	void InitializePlayer();
	void SetColor();

	UFUNCTION(Server, Unreliable)
	void ServerSetInitInfo(const FString& name, int32 num, FLinearColor color);

// 저장
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UJE_SaveGame* MySaveGame;

	FJE_CustomItemData* playerCustomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomData")
	UDataTable* PlayerCustomTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UMaterialInstanceDynamic* currentDynamicMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName HatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName GlassesTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName ShoesTag;

public:
	UFUNCTION()
	void GetCustomItemData();

	UFUNCTION()
	void SaveCustomItemData();

	UFUNCTION()
	void LoadCustomItemData();
	
};
 