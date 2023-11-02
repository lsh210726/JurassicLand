// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_CustomItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_CustomItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);



public:
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Tab_Hat;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Tab_Glasses;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category=MySettings)
	class UButton* btn_Tab_Shoes;


public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_CustomItem;

public:
	UFUNCTION()
	void OnClickedTabHat();

	UFUNCTION()
	void OnClickedTabGlasses();

	UFUNCTION()
	void OnClickedTabShoes();

	UFUNCTION()
	void SetButtonImage(UButton* btn);
	
};
