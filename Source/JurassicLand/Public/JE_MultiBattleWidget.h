// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_MultiBattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_MultiBattleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	class ULSH_NetGameInstance* gi;


public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UWidgetSwitcher* ws_MultiBattle;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_ready;
	

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_ready;

public:
	UPROPERTY()
	int32 readyCount = 0;

public:
	UFUNCTION() 
	void OnClickedReady();

	//UFUNCTION(Server, Reliable)
	//void serverReadyCountUp(int32 allReadyCount);

	//ÀÌ½ÂÇü
	bool clickOnce =true;

	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastReadyCount();

public:
	UFUNCTION(Server, Reliable)
	void ServerBattleSwitchWidget(int32 index);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastBattleSwitchWidget(int32 index);
	
};
