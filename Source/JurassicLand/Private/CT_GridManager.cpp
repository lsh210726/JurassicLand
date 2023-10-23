// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_GridManager.h"

ACT_GridManager::ACT_GridManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACT_GridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACT_GridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACT_GridManager::PopulateGrid()
{
	GridArray.Empty();

	float WorldOffset = (GridSize * WorldGridSize) * 0.5 - WorldGridSize * 0.5;

	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			float x = WorldGridSize * j - round(WorldOffset);
		}
	}
}

