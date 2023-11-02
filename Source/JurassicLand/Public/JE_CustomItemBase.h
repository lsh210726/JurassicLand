// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JE_CustomItem.h"
#include "BlueTrex.h"
#include "JE_CustomItemBase.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_CustomItemBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Custom Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Custom Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "Custom Data")
	FItemAssetData ItemAssetsData;

public:
	
	UJE_CustomItemBase();

	UFUNCTION()
	UJE_CustomItemBase*	CreateItemCopy();

	virtual void Use(ABlueTrex* character);

	
};
