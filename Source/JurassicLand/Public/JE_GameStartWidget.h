// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_GameStartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UImage* img_Logo;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_background;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UProgressBar* pb_loading;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_GameStartUI;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_skip;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	float currentTime = 0;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	float endTime = 2.0f;

	int32 loadingCount = 0;

	UPROPERTY()
	class UJE_GI* je_gi;

	class ULSH_NetGameInstance* gi;

	class ABlueTrex* player;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_nickCheck;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UEditableText* edit_nickname;

	

public:
	UFUNCTION()
	void OnClickedSkip();

	UFUNCTION()
	void OnClickedNickCheck();	

private:	
	void SwitchCanvas(int32 index);
};
