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
	class UWidgetSwitcher* ws_BattleLobbyUI;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_battleIn;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleIn;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_coin_battle;

	class ULSH_NetGameInstance* gi;
	class ABlueTrex* player;

	int32 widgetIndex = 0;

public:
	UFUNCTION()
	void OnClickedbattleIn();
	UFUNCTION()
	void battleFindSession();

private:
	void SwitchLobbyCanvas(int32 index);
	
};
