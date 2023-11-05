// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomItemActor.h"
#include "GameFramework/Actor.h" 

// Sets default values
AJE_CustomItemActor::AJE_CustomItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJE_CustomItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJE_CustomItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

