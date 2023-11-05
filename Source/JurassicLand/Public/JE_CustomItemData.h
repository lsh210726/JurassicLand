// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JE_CustomItemData.generated.h"


USTRUCT(BlueprintType)
struct JURASSICLAND_API FJE_CustomItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* playerHat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* playerGlasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class AJE_CustomItemActor* playerShoes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MySettings)
	class UMaterialInstanceDynamic* playerDynamicMat;

};


//UCLASS()
//class JURASSICLAND_API UJE_CustomItemData : public UDataTable
//{
//	GENERATED_BODY()
//	
//};
