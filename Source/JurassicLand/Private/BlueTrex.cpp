// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueTrex.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimationAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TimerHandle.h"
#include "JE_NicknameComponent.h"
#include "LSH_NetGameInstance.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"
#include "EngineUtils.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(TRexTailAttack);

// Sets default values
ABlueTrex::ABlueTrex()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*-------- Skeletal Mesh Component Setting --------*/
	TRexBody = GetMesh();

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"));
	if (tempBody.Succeeded())
	{
		TRexBody->SetSkeletalMesh(tempBody.Object);
		TRexBody->SetRelativeScale3D(FVector(0.5f));
		TRexBody->SetRelativeLocation(FVector(0, 0, -87.0f));
		TRexBody->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}
	/*--------- Spring Arm Component Setting -----------*/
//	TRexEyeArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TRexEyeArm"));
//	TRexEyeArm->SetupAttachment(GetCapsuleComponent());
//	TRexEyeArm->SetRelativeLocation(FVector(0.0f,0.0f,100.0f));
//	TRexEyeArm->SetRelativeRotation(FRotator(-15.0f,0.0f,0.0f));
//
	bUseControllerRotationYaw = true;
//	TRexEyeArm->bUsePawnControlRotation = true;
//	//TRexEye->bUsePawnControlRotation = false;
//	
//
//	/*--------- Camera Component Setting --------*/
//	TRexEye = CreateDefaultSubobject<UCameraComponent>(TEXT("TRexEye"));
//	TRexEye->SetupAttachment(TRexEyeArm);
//// 	TRexEye->SetWorldLocation(FVector(0.0f,0.0f,0.0f));
//// 	TRexEye->SetWorldRotation(FRotator(0.0f,0.0f,0.0f));

	/*--------- Enhanced Input Setting ----------*/
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>tempIMC_TRex(TEXT("/Game/7_MISC/Input/IMC_TRex.IMC_TRex"));
	if (tempIMC_TRex.Succeeded())
	{
		IMC_TRex = tempIMC_TRex.Object;
	}

	
// 	AttachToComponent(TRexEye,FAttachmentTransformRules::KeepRelativeTransform,TRexBody->GetSocketBoneName("bn_Head_10"));
// }

	/*---- Anim Import ----*/
	ConstructorHelpers::FObjectFinder<UAnimationAsset> tempTailAttack(TEXT("/Script/Engine.AnimSequence'/Game/7_MISC/Animation/BlueTRex/BlueTRex_attack_tail_2.BlueTRex_attack_tail_2'"));
	if (tempTailAttack.Succeeded())
	{
		TailAttackAnim = tempTailAttack.Object;
	}

	CharacterMovement = GetCharacterMovement();

	// 닉네임
	//nickComp = CreateDefaultSubobject<UJE_NicknameComponent>(TEXT("nickComp"));
	nicknameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("nicknameTEXT"));
	nicknameText->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "NeckSocket");
	nicknameText->SetRelativeLocation(FVector(-350, 0, 0));
	nicknameText->SetRelativeRotation(FRotator(-180, 90, 90));
	nicknameText->SetHorizontalAlignment(EHTA_Center);
	nicknameText->SetWorldSize(100);
	nicknameText->SetTextRenderColor(FColor::White);
	nicknameText->SetVisibility(false);


	//코인
	currentCoin = initialCoin;

}

// Called when the game starts or when spawned
void ABlueTrex::BeginPlay()
{
	Super::BeginPlay();
	/*-----------Enhanced Input IMC Set up---------*/
	pc = Cast<APlayerController>(GetController());
	if (pc != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
			SubSystem->AddMappingContext(IMC_TRex, 0);
	}

	
	// 닉네임	

	// 지은 - 초기 설정
	if (GetController() != nullptr && GetController()->IsLocalController())
	{
		gi = GetGameInstance<ULSH_NetGameInstance>();
		ServerSetInitInfo(gi->playerCustomInfo.dinoName, gi->playerCustomInfo.dinoMeshNum, gi->playerCustomInfo.dinoColor);
	}

	//nicknameText->SetText(FText::FromString(playerName));

	// 캐릭터 초기화 지연 실행
	FTimerHandle initHandler;
	GetWorldTimerManager().SetTimer(initHandler, this, &ABlueTrex::InitializePlayer, 1.0f, false);

}

// Called every frame
void ABlueTrex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!btickStop)
	{
		if (TRexHP <= 0.f)
		{
			bIsHpZero = true;
			gi->isEnd = true;
			btickStop = true;
		}
	}
	

}

// Called to bind functionality to input
void ABlueTrex::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*-----------Enhanced Input Bind Setting---------*/
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		SetupPlayerEnhancedInputComponent(EnhancedInputComponent, inputActions);
	}
}

void ABlueTrex::SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> InputActions)
{
	EnhancedInputComponent->BindAction(InputActions[0], ETriggerEvent::Triggered, this, &ABlueTrex::TRexMove);
	EnhancedInputComponent->BindAction(InputActions[1],ETriggerEvent::Triggered,this,&ABlueTrex::TRexLook);
	EnhancedInputComponent->BindAction(InputActions[2], ETriggerEvent::Started, this, &ABlueTrex::TRexTailAttack);
}

void ABlueTrex::TRexMove(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valY = tempVal.Y;
	float valX = tempVal.X;

	FRotator CurrControlRotation = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, CurrControlRotation.Yaw, CurrControlRotation.Roll)), valX);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, CurrControlRotation.Yaw, 0.0f)), valY);
	

}

void ABlueTrex::TRexLook(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valX = tempVal.X;
	float valY = tempVal.Y;
// 
	AddControllerYawInput(valX);
	AddControllerPitchInput(valY);
	/*TRexEyeArm->SetRelativeRotation(TRexEyeArm->Getrotation)*/
	//need Debug : 가만히 있을 때, 카메라만 돌아서 시선만 이동해야하는데 캐릭터도 같이 돌아간다. 

}

void ABlueTrex::TRexTailAttack_Implementation(const FInputActionValue& Val)
{

	if(TailAttackAnim!=nullptr&&TailAttack==false)
	{
		
		TailAttack = true;
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		this->bUseControllerRotationYaw = false;
		
	}
}


void ABlueTrex::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlueTrex, TRexHP);
	DOREPLIFETIME(ABlueTrex, bIsHpZero);
	DOREPLIFETIME(ABlueTrex, initialCoin);
	DOREPLIFETIME(ABlueTrex, currentCoin);
	DOREPLIFETIME(ABlueTrex, playerName);
	DOREPLIFETIME(ABlueTrex, playerColor);
	DOREPLIFETIME(ABlueTrex, playerMeshNumber);


}

void ABlueTrex::InitializePlayer()
{
	// 닉네임 설정
	if (nicknameText)
	{
		nicknameText->SetText(FText::FromString(playerName));
	}

	// 컬러 설정
	UMaterialInterface* mat1 = GetMesh()->GetMaterial(0);

	UMaterialInstanceDynamic* dynamicMat1 = UMaterialInstanceDynamic::Create(mat1, this);

	GetMesh()->SetMaterial(0, dynamicMat1);

	dynamicMat1->SetVectorParameterValue(FName("MyColor"), playerColor);
}

void ABlueTrex::ServerSetInitInfo_Implementation(const FString& name, int32 num, FLinearColor color)
{
	playerName = name;
	playerMeshNumber = num;
	playerColor = color;

}
