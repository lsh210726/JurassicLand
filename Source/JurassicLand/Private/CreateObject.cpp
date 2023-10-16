// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateObject.h"

ACreateObject::ACreateObject()
{
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	meshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (tmpMesh.Succeeded())
	{
		meshComp->SetStaticMesh(tmpMesh.Object);
	}
}

void ACreateObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreateObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

