// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "JE_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
	UJE_SaveGame();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* myHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* myGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* myShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class UMaterialInstanceDynamic* myCustomDynamicMat;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	FName myHatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	FName myGlassesTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	FName myShoesTag;
};
