// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_TypeListViewWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_TypeListViewWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	class ULSH_NetGameInstance* gi;
	class ABlueTrex* player;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_type;

public:
	UFUNCTION()
	void OnClickedType();
};
