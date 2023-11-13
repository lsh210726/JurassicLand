// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "JE_CustomItemData.h"
#include "BasePlayer.generated.h"

UCLASS()
class JURASSICLAND_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/*--------- Character Component -----------*/
public:
	//SkeletalMesh
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class USkeletalMeshComponent* PlayerBody;
	
	//Spring Arm
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class USpringArmComponent* PlayerCamArm;

	//Camera
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCameraComponent* PlayerCam;

	//Collision_ Head
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerHeadCollision;
	
	//Collision_ UpperBody
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerUpperBodyCollision;
	
	//Collision_ Tail
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UCapsuleComponent* PlayerTailCollision;

	//HP Bar Widget
	UPROPERTY(EditAnywhere, Category = CharacterSettings, BlueprintReadWrite)
	class UWidgetComponent* HP_Bar;


	/********** Player Common Value *************/
public:
	/*State - HP, Speed, Power, Defence*/
	

	
	//State_HP(Damage System Value)
	//HP동기화
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float State_HP = 50; 
	
	//HP 변수 동기화 위한 함수
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//noDamageTime(공격 맞고나서 몇초간 무적)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	bool noDamageTime = false;

	//State_Speed
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float SpeedStat = 4.0f;

	//State_Power
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float PowerStat = 6.0f;

	//State_Defence
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float DefenceStat = 5.0f;

	//State_Temp : Player State Before Buff
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = CharacterStat, BlueprintReadWrite)
	float TempStat = 0.0f;


	/*--------------- Value about Skill ------------*/
	//Special Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int SpecialSkill = 0;
	
	//Buff Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int BuffSkill = 0;

	/*----------- Skill Control Value ------------*/
	//ICE Attack Forward Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackFwdVector;
	
	//ICE Attack Location Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackLocVector;

	//Special Skill Cool Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", BlueprintReadWrite)
	bool SCoolTime = false;
	
	//Buff Skill Cool Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", BlueprintReadWrite)
	bool BCoolTime = false;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float buffCool = 5.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float SpecialCool = 5.0f;

// 	Basic Skill Cool Time
// 		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillControl, BlueprintReadWrite)
// 		bool CoolTime_BasicSkill = false;


/*--------- Animation Control value ----------*/
	
	//Turn Left
	UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnLeft = false;
	 
	 //Turn Right
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnRight = false;
	 
	 //Laser Beam
	 UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bLaserBeam = false;

	 //TailAttack
	  UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTailAttack= false;
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bIsNoHit = true;
	 
	 //Roar
	  UPROPERTY(Replicated,EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bRoar= false;
	 
	 //Bite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bBite = false;
	 
	 //ICE Stalagmite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bICEStalagmite = false;

	 //Breath Flame
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bFlameOnOff = false;

/*---------- Customize System Value -------------*/
	  //GlassesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> GlassesActorClass;
	  
	  //HatActorClass
	   UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> HatActorClass;

	  //RShoesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> RShoesActorClass;
	  
	  //LShoesActorClass
	  UPROPERTY(EditAnywhere, Category = CustomizeSys, BlueprintReadWrite)
	  TSubclassOf<class AActor> LShoesActorClass;

	  /*----- General Value ----------*/
public:
	class APlayerController* pc;
	class UCharacterMovementComponent* CharacterMovement;

	  /*---------- Enhanced Input ---------------*/
	  //Enhanced Input Component
	  UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Input)
	  class UMoveComp* MoveComp; 

	  //Context
	  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input)
	  class UInputMappingContext* IMC_Player;

	  //InputActions
	  UPROPERTY(EditAnywhere,Category=Input)
	  TArray<class UInputAction*> inputActions;

 	  public:
 	// hp - 지은
 	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "StateWidget")//HP동기화
 	bool bIsHpZero = false;	
 
 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StateWidget")
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

	// 안경 변수
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerGlasses;

	// 신발 변수  
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Custom)
	FName playerShoes;

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

// 메쉬 커스텀
public:

	// 메쉬 경로 저장한 배열
	TArray<FString> meshPathList = { TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Raptor/Model/Raptor_HumanIK.Raptor_HumanIK'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Dinosaurus_Stegosaurus/Models/SK_Stegosaurus.SK_Stegosaurus'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };
	
	// 메쉬에 맞는 material
	TArray<FString> matPathList = { TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Raptor/Model/DromaMESH_DromaBodyM.DromaMESH_DromaBodyM'"),
									TEXT("/Script/Engine.Material'/Game/4_SK/Dinosaurus_Stegosaurus/Models/Materials/M_Stegosaurus_Green.M_Stegosaurus_Green'"),
									TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Triceratops/Meshes/SK_Triceratops.SK_Triceratops'"), };


	// 메쉬 변경 함수
	UFUNCTION()
	void SetMesh();

	// 메쉬 초기 설정
	UFUNCTION()
	void CustomMesh();
	/*------- LockOnSystem -----------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LockOnSystem)
	class AActor* LockOnTarget;

// 스킬 프리셋
public:
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	bool IsSetPreset = false;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 currBuffskillNum;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 currSpecialskillNum;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* currplayerSpecialSkillImg;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Skill")
	class UTexture2D* currplayerBuffSkillImg;

	// 스킬 사용하는 키에 따른 쿨타임 인덱스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 coolTimeIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<class UJE_BattleWidget> battlewidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
 	class UJE_BattleWidget* battleUI;
};
