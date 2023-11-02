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

USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText UsageText;
};


USTRUCT(BlueprintType)
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;
};


USTRUCT(BlueprintType)
struct JURASSICLAND_API FJE_CustomItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Data")
	FItemAssetData ItemAssetsData;

};