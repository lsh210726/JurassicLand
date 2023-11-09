// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_SkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_SkillWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	class ULSH_NetGameInstance* gi;
	class ABlueTrex* player;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_fire;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_laser;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_ice;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_bite;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_tail;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_speedup;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_defenceup;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_attackup;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_roar;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset3;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<UImage*> presetArray;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<UTexture2D*> presetImgArray;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<FString> presetImgStr;

	//const FSlateBrush* FireBrush;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UTexture2D* skillImg;
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UTexture2D* presetImg1;
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UTexture2D* presetImg2;
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UTexture2D* presetImg3;

public:
	bool isFire = false;
	bool isLaser = false;
	bool isIce = false;
	bool isbite = false;
	bool istail = false;
	bool isSpeedUP = false;
	bool isDefenceUP = false;
	bool isAttackUP = false;


public:
	UFUNCTION()
	void OnClickedFire();

	UFUNCTION()
	void OnClickedLaser();

	UFUNCTION()
	void OnClickedIce();

	UFUNCTION()
	void OnClickedBite();

	UFUNCTION()
	void OnClickedTail();

	UFUNCTION()
	void OnClickedSpeedUP();

	UFUNCTION()
	void OnClickedDefenceUP();
	
	UFUNCTION()
	void OnClickedAttackUP();

	UFUNCTION()
	void SetPreset();

	UFUNCTION()
	void FindPreset();

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_skill_backtomain;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_skill_save;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_skill_load;

public:
	UFUNCTION()
	void OnClickedSkillTOMain();
	
};
