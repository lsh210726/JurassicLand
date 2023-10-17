// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateObject.h"
#include "CT_ClickableComponent.h"
#include "CT_CreateComponent.h"


ACreateObject::ACreateObject()
{
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(RootComponent);

	//meshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	meshComp->SetCollisionProfileName(TEXT("CreateObject"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (tmpMesh.Succeeded())
	{
		meshComp->SetStaticMesh(tmpMesh.Object);
	}

	createComp = CreateDefaultSubobject<UCT_CreateComponent>(TEXT("CreateComponent"));
	clickComp = CreateDefaultSubobject<UCT_ClickableComponent>(TEXT("ClickableComponent"));
}

void ACreateObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreateObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

