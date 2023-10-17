// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CT_GridManager.generated.h"

UCLASS()
class JURASSICLAND_API ACT_GridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACT_GridManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 GridSize = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	int32 WorldGridSize = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	TArray<int32> GridArray;

public:
	
	void PopulateGrid();
};
