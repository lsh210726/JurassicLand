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
	//State_HP
	UPROPERTY(EditAnywhere, Category = CharacterStat, BlueprintReadWrite)
	int State_HP = 100;

	//State_Speed
	UPROPERTY(EditAnywhere, Category = CharacterStat, BlueprintReadWrite)
	float State_Speed = 4.0f;

	//State_Power
	UPROPERTY(EditAnywhere, Category = CharacterStat, BlueprintReadWrite)
	float State_Power = 6.0f;

	//State_Defence
	UPROPERTY(EditAnywhere, Category = CharacterStat, BlueprintReadWrite)
	float State_Defence = 5.0f;

	//State_Temp : Player State Before Buff
	UPROPERTY(EditAnywhere, Category = CharacterStat, BlueprintReadWrite)
	float State_Temp = 0.0f;


	/*--------------- Value about Skill ------------*/
	//Special Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int SpecialSkill = 0;
	
	//Buff Skill Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int BuffSkill = 0;

	//Basic Attack Selection
	UPROPERTY(EditAnywhere, Category = Player_SkillSelection, BlueprintReadWrite)
	int BasicAttack = 0;



	/*----------- Skill Control Value ------------*/
	//ICE Attack Forward Vector
	UPROPERTY(EditAnywhere, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackFwdVector;
	
	//ICE Attack Location Vector
	UPROPERTY(EditAnywhere, Category = SkillControl, BlueprintReadWrite)
	FVector IceAttackLocVector;

	//Special Skill Cool Time
	UPROPERTY(EditAnywhere, Category = SkillControl, BlueprintReadWrite)
	bool CoolTime_SpecialSkill = false;
	
	//Buff Skill Cool Time
	UPROPERTY(EditAnywhere, Category = SkillControl, BlueprintReadWrite)
	bool CoolTime_BuffSkill = false;
	
	//Basic Skill Cool Time
	UPROPERTY(EditAnywhere, Category = SkillControl, BlueprintReadWrite)
	bool CoolTime_BasicSkill = false;

/*--------- Animation Control value ----------*/
	//Turn Left
	UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnLeft = false;
	 
	 //Turn Right
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bTurnRight = false;
	 
	 //Laser Beam
	 UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bLaserBeam = false;

	 //Roar
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bRoar= false;
	 
	 //Bite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bBite = false;
	 
	 //ICE Stalagmite
	  UPROPERTY(EditAnywhere, Category = AnimationControl, BlueprintReadWrite)
	 bool bICEStalagmite = false;

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
	  UPROPERTY(VisibleAnywhere, Category = Input)
	  class UMoveComp* MoveComp; 

	  //Context
	  UPROPERTY(VisibleAnywhere, Category = Input)
	  class UInputMappingContext* IMC_Player;

	  //InputActions
	  UPROPERTY(EditAnywhere,Category=Input)
	  TArray<class UInputAction*> inputActions;
};
