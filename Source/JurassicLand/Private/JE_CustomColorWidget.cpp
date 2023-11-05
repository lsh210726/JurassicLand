// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomColorWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"

void UJE_CustomColorWidget::NativeConstruct()
{
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	btn_red->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnRedClicked);
	btn_yellow->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnYellowClicked);
	btn_blue->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnBlueClicked);
	btn_green->OnClicked.AddDynamic(this, &UJE_CustomColorWidget::OnGreenClicked);
}

void UJE_CustomColorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_CustomColorWidget::OnYellowClicked()
{
	if (currentColor != FLinearColor::Yellow)
	{
		currentColor = FLinearColor::Yellow;
	}
	else
	{
		currentColor = FLinearColor::White;
	}
	
	gi->playerCustomInfo.dinoColor = currentColor;
	player->SetColor();

	//// 컬러 설정
	//UMaterialInterface* mat1 = player->GetMesh()->GetMaterial(0);
	//FString Message = FString::Printf(TEXT("%s"), *mat1->GetName());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

	//UMaterialInstanceDynamic* dynamicMat1 = UMaterialInstanceDynamic::Create(mat1, this);

	//player->GetMesh()->SetMaterial(0, dynamicMat1);

	//dynamicMat1->SetVectorParameterValue(FName("MyColor"), currentColor);

	


}

void UJE_CustomColorWidget::OnBlueClicked()
{	
	if (currentColor != FLinearColor::Blue)
	{
		currentColor = FLinearColor::Blue;
	}
	else
	{
		currentColor = FLinearColor::White;
	}
	gi->playerCustomInfo.dinoColor = currentColor;
	player->SetColor();

}

void UJE_CustomColorWidget::OnGreenClicked()
{
	if (currentColor != FLinearColor::Green)
	{
		currentColor = FLinearColor::Green;
	}
	else
	{
		currentColor = FLinearColor::White;
	}
	
	gi->playerCustomInfo.dinoColor = currentColor;
	player->SetColor();

}

void UJE_CustomColorWidget::OnRedClicked()
{
	if (currentColor != FLinearColor::Red)
	{
		currentColor = FLinearColor::Red;
	}
	else
	{
		currentColor = FLinearColor::White;
	}
	
	gi->playerCustomInfo.dinoColor = currentColor;
	player->SetColor();

}

