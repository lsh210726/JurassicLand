// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_SkillWidget.h"
#include "LSH_NetGameInstance.h"
#include "BlueTrex.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"


void UJE_SkillWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	presetArray.Add(img_preset1);
	presetArray.Add(img_preset2);
	presetArray.Add(img_preset3);

	presetImgArray.Add(presetImg1);
	presetImgArray.Add(presetImg2);
	presetImgArray.Add(presetImg3);

	btn_fire->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedFire);
	btn_laser->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedLaser);
	btn_ice->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedIce);
	btn_foot->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedFoot);
	btn_speedup->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedSpeedUP);
	btn_defenceup->OnClicked.AddDynamic(this, &UJE_SkillWidget::OnClickedDefenceUP);

}

void UJE_SkillWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_SkillWidget::OnClickedFire()
{

	const FSlateBrush* FireBrush = &btn_fire->WidgetStyle.Normal;
	skillImg = Cast<UTexture2D>(FireBrush->GetResourceObject());

	FString Message2 = FString::Printf(TEXT("%s"), *skillImg->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message2);

	if (!isFire)
	{
		SetPreset();

		isFire = true;
	}
	else
	{
		FindPreset();
		isFire = false;

	}
	
}

void UJE_SkillWidget::OnClickedLaser()
{
	if (!isLaser)
	{
		const FSlateBrush* LaserBrush = &btn_laser->WidgetStyle.Normal;
		skillImg = Cast<UTexture2D>(LaserBrush->GetResourceObject());

		FString Message = FString::Printf(TEXT("%s"), *skillImg->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

		SetPreset();

		isLaser = true;
	}
	
}

void UJE_SkillWidget::OnClickedIce()
{
	if (!isIce)
	{
		const FSlateBrush* IceBrush = &btn_ice->WidgetStyle.Normal;
		skillImg = Cast<UTexture2D>(IceBrush->GetResourceObject());

		FString Message = FString::Printf(TEXT("%s"), *skillImg->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

		SetPreset();

		isIce = true;
	}
	
}

void UJE_SkillWidget::OnClickedFoot()
{
	if (!isFoot)
	{
		const FSlateBrush* FootBrush = &btn_foot->WidgetStyle.Normal;
		skillImg = Cast<UTexture2D>(FootBrush->GetResourceObject());

		FString Message = FString::Printf(TEXT("%s"), *skillImg->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

		SetPreset();

		isFoot = true;
	}
	
}

void UJE_SkillWidget::OnClickedSpeedUP()
{
	if (!isSpeedUP)
	{
		const FSlateBrush* FootBrush = &btn_speedup->WidgetStyle.Normal;
		skillImg = Cast<UTexture2D>(FootBrush->GetResourceObject());

		FString Message = FString::Printf(TEXT("%s"), *skillImg->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

		SetPreset();

		isSpeedUP = true;
	}
	
}

void UJE_SkillWidget::OnClickedDefenceUP()
{
	if (!isDefenceUP)
	{
		const FSlateBrush* DefenceBrush = &btn_defenceup->WidgetStyle.Normal;
		skillImg = Cast<UTexture2D>(DefenceBrush->GetResourceObject());

		FString Message = FString::Printf(TEXT("%s"), *skillImg->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);

		SetPreset();

		isDefenceUP = true;
	}
	
}

void UJE_SkillWidget::SetPreset()
{
	
	presetImg1 = Cast<UTexture2D>(img_preset1->GetBrush().GetResourceObject());
	presetImg2 = Cast<UTexture2D>(img_preset2->GetBrush().GetResourceObject());
	presetImg3 = Cast<UTexture2D>(img_preset3->GetBrush().GetResourceObject());

	if (presetImg1 == nullptr)
	{
		img_preset1->SetBrushResourceObject(skillImg);
	}
	else if (presetImg2 == nullptr)
	{
		img_preset2->SetBrushResourceObject(skillImg);

	}
	else if (presetImg3 == nullptr)
	{
		img_preset3->SetBrushResourceObject(skillImg);

	}
	else
	{
		return;
	}
	FString Message = presetImg1 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message);

	FString Messag1 = presetImg2 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Messag1);

	FString Message2 = presetImg3 == nullptr ? FString("None") : FString("Yes");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Message2);
	
	//if()
}

void UJE_SkillWidget::FindPreset()
{
	for (int i = 0; i < 3; i++)
	{		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%d"),i));

		if (presetImgArray[i])
		{
			FString Message1 = FString::Printf(TEXT("%s"), *presetArray[i]->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Message1);
			FString Message21 = FString::Printf(TEXT("%s"), *skillImg->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Message21);

			if (presetImgArray[i]->GetName() == skillImg->GetName())
			{
				UTexture2D* EmptyTexture = nullptr;
				presetArray[i]->SetBrushResourceObject(EmptyTexture);
				break;
			}
		}
		

	}
}
