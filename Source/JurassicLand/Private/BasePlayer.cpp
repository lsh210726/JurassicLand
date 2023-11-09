// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
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
#include "JE_CustomItemActor.h"
#include "JE_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" 
#include "UObject/ConstructorHelpers.h"
#include "JE_CustomPlayerController.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MoveComp.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Skeletal Mesh Component
	PlayerBody = GetMesh();
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT(""));

	PlayerBody->SetupAttachment(RootComponent);

	if (tempBody.Succeeded())
	{
		PlayerBody->SetSkeletalMesh(tempBody.Object);
	}

	//Spring Arm
	PlayerCamArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCamArm"));
	PlayerCamArm->SetupAttachment(RootComponent);
	PlayerCamArm->TargetArmLength = 400.0f;
	PlayerCamArm->SocketOffset = FVector(0.0f, 0.0f, 200.0f);

	//Camera
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCam"));
	PlayerCam->SetupAttachment(PlayerCamArm);
	PlayerCam->SetRelativeRotation(FRotator(0.0, 17.0f, 0.0f));
	PlayerCam->FieldOfView = 75.0f;

	//HP Bar Widget
	HP_Bar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_Bar"));
	HP_Bar->SetupAttachment(PlayerBody);
	ConstructorHelpers::FClassFinder<UUserWidget> tempHPBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/2_BP/Widget/BP_LSH_BPHPWidget.BP_LSH_BPHPWidget_C'"));
	if (tempHPBar.Succeeded())
	{
		HP_Bar->SetWidgetClass(tempHPBar.Class);
	}

	//collision_Head
	PlayerHeadCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerHeadCollision"));

	//collision_Upper Body
	PlayerUpperBodyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerUpperCollision"));

	//collision_Tail
	PlayerTailCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerTailCollision"));

	//Enhanced Input
	ConstructorHelpers::FObjectFinder<UInputMappingContext>tempEnhancedInputComp(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/7_MISC/Input/IMC_Player.IMC_Player'"));
	if (tempEnhancedInputComp.Succeeded())
	{
		IMC_Player = tempEnhancedInputComp.Object;
	}

	MoveComp = CreateDefaultSubobject<UMoveComp>(TEXT("MoveComp"));
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	pc = Cast<APlayerController>(GetController());
	if (pc != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(IMC_Player, 0);
		}
	}
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MoveComp->SetupPlayerEnhancedInputComponent(EnhancedInputComponent, inputActions);
	}
}

