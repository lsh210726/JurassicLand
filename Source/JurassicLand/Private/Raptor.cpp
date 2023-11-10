// Fill out your copyright notice in the Description page of Project Settings.


#include "Raptor.h"

ARaptor::ARaptor()
{

	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempRaptorBody(TEXT("/Script/Engine.SkeletalMesh'/Game/4_SK/Raptor/Model/Raptor_HumanIK.Raptor_HumanIK'"));
	
	if (tempRaptorBody.Succeeded())
	{
		
		PlayerBody->SetSkeletalMesh(tempRaptorBody.Object);
		PlayerBody->SetRelativeLocation(FVector(0.0f,0.0f,-88.0f));
		PlayerBody->SetRelativeRotation(FRotator(0.0,-90.0f,0.0f));
		PlayerBody->SetRelativeScale3D(FVector(3.0f));
	}
}
