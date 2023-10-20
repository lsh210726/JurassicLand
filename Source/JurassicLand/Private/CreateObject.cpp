// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateObject.h"

// Sets default values
ACreateObject::ACreateObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreateObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreateObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

