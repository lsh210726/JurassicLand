// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_CustomListViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_CustomListViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MySettings)
	class UDataTable* CustomItemTable;

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UButton* btn_item1;
// 
// 	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
// 	class UButton* btn_item2;
// 
// 	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
// 	class UButton* btn_item3;
	

	
};
