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
	currentColor = FLinearColor::Yellow;
	gi->playerCustomInfo.dinoColor = currentColor;
	player->InitializePlayer();

}

void UJE_CustomColorWidget::OnBlueClicked()
{
	currentColor = FLinearColor::Blue;
	gi->playerCustomInfo.dinoColor = currentColor;

}

void UJE_CustomColorWidget::OnGreenClicked()
{
	currentColor = FLinearColor::Green;
	gi->playerCustomInfo.dinoColor = currentColor;

}

void UJE_CustomColorWidget::OnRedClicked()
{
	currentColor = FLinearColor::Red;
	gi->playerCustomInfo.dinoColor = currentColor;

}

