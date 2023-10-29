// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_BattleWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_BattleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	class ABlueTrex* player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = MySettings)
	class UWidgetSwitcher* ws_Battle;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_skill_roar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_skill_tail;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_skill_foot;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UButton* btn_toMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleloading;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleStart;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_hp1;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_hp2;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_roar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_tail;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_skill_foot;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_battleresult;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_toMain;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UProgressBar* pb_playerHP_1;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UProgressBar* pb_playerHP_2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_player_win;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = MySettings)
	class UImage* img_player_lose;

	UPROPERTY(VisibleAnywhere, Transient, meta = (BindWidgetAnim), Category = MySettings)
	class UWidgetAnimation* startText;

	FTimerHandle initHandler;

public:	
	UFUNCTION()
	void LoadingUI();

	UFUNCTION()
	void StartUIAnim();

	
};
