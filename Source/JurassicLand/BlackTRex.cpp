// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackTRex.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABlackTRex::ABlackTRex()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*-------- Skeletal Mesh Component Setting --------*/
	TRexBody = GetMesh();

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlackTRex/Meshes/SM_Tyrannosaurus_Rex_Sue_T_Pose.SM_Tyrannosaurus_Rex_Sue_T_Pose'"));
	if (tempBody.Succeeded())
	{
		TRexBody->SetSkeletalMesh(tempBody.Object);
		TRexBody->SetRelativeScale3D(FVector(0.65f));
		TRexBody->SetRelativeLocation(FVector(0, 0, -87.0f));
		TRexBody->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}

	/*--------- Camera Component Setting --------*/
	TRexEye = CreateDefaultSubobject<UCameraComponent>(TEXT("TRexEye"));
	TRexEye->SetupAttachment(RootComponent);
	TRexEye->SetRelativeLocation(FVector(372.0f, 0.0f, 155.0f));

	/*--------- Enhanced Input Setting ----------*/
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>tempIMC_TRex(TEXT("/Game/7_MISC/Input/IMC_TRex.IMC_TRex"));
	if (tempIMC_TRex.Succeeded())
	{
		IMC_TRex = tempIMC_TRex.Object;
	}

	/*------------- Animation Blueprints Setting---------------*/
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> BP_BlackTRexAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/4_SK/BlackTRex/Blueprints/ABP_Trex_SUE_Blueprint.ABP_Trex_SUE_Blueprint'"));
	
	TRexBody->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	if (BP_BlackTRexAnim.Succeeded())
	{
		TRexBody->SetAnimClass(BP_BlackTRexAnim.Object->GetAnimBlueprintGeneratedClass());
	}
	
}

// Called when the game starts or when spawned
void ABlackTRex::BeginPlay()
{
	Super::BeginPlay();

	/*-----------Enhanced Input IMC Set up---------*/
	pc = Cast<APlayerController>(GetController());
	if (pc != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
			SubSystem->AddMappingContext(IMC_TRex, 0);
	}
}

// Called every frame
void ABlackTRex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlackTRex::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*-----------Enhanced Input Bind Setting---------*/
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		SetupPlayerEnhancedInputComponent(EnhancedInputComponent, InputActions);
	}
}

/*----------Enhanced Input Function Bind------------------*/
void ABlackTRex::SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, TArray<class UInputAction*> inputActions)
{
	EnhancedInputComponent->BindAction(InputActions[0],ETriggerEvent::Triggered,this,&ABlackTRex::TRexMove);
}

/*-----------------Enhanced Input Functions-------------------*/
void ABlackTRex::TRexMove(const FInputActionValue& Val)
{
	FVector2D tempVal = Val.Get<FVector2D>();
	float valY = tempVal.Y;
	float valX = tempVal.X;

	FRotator CurrControlRotation = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, CurrControlRotation.Yaw, CurrControlRotation.Roll)), valX);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, CurrControlRotation.Yaw, 0.0f)), valY);
}

