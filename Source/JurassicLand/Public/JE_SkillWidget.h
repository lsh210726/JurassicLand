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
	class UButton* btn_foot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_speedup;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UButton* btn_defenceup;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	class UImage* img_preset3;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	TArray<UImage*> presetArray;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget), Category = MySettings)
	TArray<UTexture2D*> presetImgArray;

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
	bool isFoot = false;
	bool isSpeedUP = false;
	bool isDefenceUP = false;


public:
	UFUNCTION()
	void OnClickedFire();

	UFUNCTION()
	void OnClickedLaser();

	UFUNCTION()
	void OnClickedIce();

	UFUNCTION()
	void OnClickedFoot();

	UFUNCTION()
	void OnClickedSpeedUP();

	UFUNCTION()
	void OnClickedDefenceUP();

	UFUNCTION()
	void SetPreset();

	UFUNCTION()
	void FindPreset();
	
};
