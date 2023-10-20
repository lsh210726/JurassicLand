// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackTRex.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h"

// Sets default values
ABlackTRex::ABlackTRex()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pc = Cast<APlayerController>(GetController());

/*-------- Skeletal Mesh Component Setting --------*/
	TRexBody = GetMesh();
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlackTRex/Meshes/SM_Tyrannosaurus_Rex_Sue_T_Pose.SM_Tyrannosaurus_Rex_Sue_T_Pose'"));
	if (tempBody.Succeeded())
	{
		TRexBody->SetSkeletalMesh(tempBody.Object);
		TRexBody->SetRelativeScale3D(FVector(0.5f));
		TRexBody->SetRelativeLocation(FVector(0, 0, -87.0f));
		TRexBody->SetRelativeRotation(FRotator(0, -90.0f, 0));
	}
	
/*--------- Camera Component Setting --------*/
	TRexEye = CreateDefaultSubobject<UCameraComponent>(TEXT("TRexEye"));
	TRexEye->SetupAttachment(RootComponent);
	TRexEye->SetRelativeLocation(FVector(290.0f, 0.0f, 100.0f));

/*--------- Enhanced Input Setting ----------*/
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>tempIMC_TRex(TEXT("/Game/7_MISC/Input/IMC_TRex.IMC_TRex"));
	if (tempIMC_TRex.Succeeded())
	{
		IMC_TRex = tempIMC_TRex.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>tempIA_Move(TEXT("/Game/7_MISC/Input/IA_Move.IA_Move"));
	if (tempIA_Move.Succeeded())
	{
		IA_Move = tempIA_Move.Object;
	}

}

// Called when the game starts or when spawned
void ABlackTRex::BeginPlay()
{
	Super::BeginPlay();
	
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

}

/*-----------------Enhanced Bind Action Functions-------------------*/
void ABlackTRex::TRexMove(const FInputActionValue& Val)
{
	
}

