// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_BattleLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_BattleLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* img_map;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_BattleLobbyUI;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_mapchoice;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_mapcheck;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_mapchoice;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_check;

public:
	UFUNCTION()
	void OnClickedCheck();

	UFUNCTION()
	void OnClickedChoice();

private:
	void SwitchLobbyCanvas(int32 index);
	
};
