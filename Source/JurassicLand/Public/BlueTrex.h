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

/*---------------------------- 지은 ----------------------------*/
// 플레이어 정보 : 닉네임, 메쉬, 컬러
public:

	class ULSH_NetGameInstance* gi;
	
	// 닉네임 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FString playerName = "BlueTrex";

	// 색 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FLinearColor playerColor = FLinearColor::White;

	// 메쉬 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	int32 playerMeshNumber = 0;

// 플레이어 정보 : 모자, 안경, 신발
public:
	// 모자 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerHat;
	//TArray<FName> playerHat;

	// 안경 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerGlasses;
	//TArray<FName> playerGlasses;

	// 신발 변수  
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerShoes;
	//TArray<FName> playerShoes;

public:
	// 닉네임 ui component
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UJE_NicknameComponent* nickComp;*/

	// 닉네임 textrendercomponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Nickname")
	class UTextRenderComponent* nicknameText;

//코인
public:
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float initialCoin = 500.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category=coin)
	float currentCoin = 0.0f;

//컬러 커스텀
public:
	class UMaterialInterface* CustomMat;
	class UMaterialInterface* InitialMat;
	class UMaterialInterface* currMat;
	class UMaterialInstanceDynamic* dynamicMat1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	bool IsColor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	bool IsColorCustom = false;

// 메쉬 커스텀
public:

	TArray<FString> meshPathList = { TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"),
									TEXT("/Game/Characters/Mannequins/Meshes/SKM_Quinn"),
									TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin"),
									TEXT("/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin"), };
	

public:
	//커스텀 아이템, 커스텀 컬러 및 플레이어 정보 실행 함수
	UFUNCTION()
	void InitializePlayer();

	// 커스텀 컬러 플레이어 정보 설정 함수(멀티캐스트)
	UFUNCTION(BlueprintCallable)
	void SetColor();

	// 커스텀 컬러 초기 설정
	UFUNCTION()
	void CustomColor();

	// 커스텀 아이템 설정 함수, 블루프린트에 정의
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InitialCustomMulti();

	// 플레이어 정보 설정 함수
	UFUNCTION(Server, Reliable)
	void ServerSetInitInfo(FPlayerCustomInfo initInfo);

	// 플레이어 커스텀 아이템 설정 함수
	UFUNCTION(Server, Reliable)
	void ServerSetCustomItemInfo(FPlayerCustomItemInfo customItemInfo);

// 저장
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UJE_SaveGame* MySaveGame;

	// 커스텀 아이템 데이터 테이블 정보
	FJE_CustomItemData* playerCustomData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomData")
	UDataTable* PlayerCustomTable;

	// 커스텀 아이템 저장 변수들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class AJE_CustomItemActor* currentShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	class UMaterialInstanceDynamic* currentDynamicMat;

	// 커스텀 액터의 태그 저장 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName HatTag;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName GlassesTag;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "CustomData")
	FName ShoesTag;

public:
	UFUNCTION()
	void GetCustomItemData();

	UFUNCTION()
	void SaveCustomItemData();

	UFUNCTION()
	void LoadCustomItemData();
	
};
 