// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade_BlueTRex.h"

AUpgrade_BlueTRex::AUpgrade_BlueTRex()
{
	PrimaryActorTick.bCanEverTick = true;

	/*------------ Initial Settings ---------------*/
	//Skeletal Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempTrexBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/BlueTRex/SK_TRex.SK_TRex'"));
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/4_SK/BlueTRex/MAT_TRex.MAT_TRex'"));
	if (tempTrexBody.Succeeded())
	{
		PlayerBody->SetSkeletalMesh(tempTrexBody.Object);
		PlayerBody->SetRelativeLocation(FVector(0.0f, 0.0f, -87.0f));
		PlayerBody->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		PlayerBody->SetRelativeScale3D(FVector(0.5f));
		if(tempMat.Succeeded()) PlayerBody->SetMaterial(0,tempMat.Object);
	}

	//Anim_BP
	ConstructorHelpers::FClassFinder<UAnimInstance> tempAnimBP(TEXT("/Script/Engine.AnimBlueprint'/Game/4_SK/BlueTRex/BluePrints/ABP_BlueTRex.ABP_BlueTRex_C'"));
	PlayerBody->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	if (tempAnimBP.Succeeded())
	{
		PlayerBody->SetAnimClass(tempAnimBP.Class);
	}

}
