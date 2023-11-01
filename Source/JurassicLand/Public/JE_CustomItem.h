// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JE_CustomItem.generated.h"

UENUM()
enum class EItemType : uint8
{
	Hat UMETA(DisplayName = "Hat"),
	Glasses UMETA(DisplayName = "Glasses"),
	Shoes UMETA(DisplayName = "Shoes"),

};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(EditAnywhere)
	FText UsageText;
};


USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};

UCLASS()
class JURASSICLAND_API UJE_CustomItem : public UDataTable
{
	GENERATED_BODY()

	EItemType ItemType;

	FItemTextData ItemTextData;

	FItemAssetData ItemAssetsData;
	
};
