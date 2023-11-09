// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_TypeListViewWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"

void UJE_TypeListViewWidget::NativeConstruct()
{
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();
	
	btn_type->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType);
	btn_type_1->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType2);
	btn_type_2->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType3);
	btn_type_3->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType4);
}

void UJE_TypeListViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UJE_TypeListViewWidget::OnClickedType()
{
	gi->playerCustomInfo.dinoMeshNum = 0;

	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType2()
{
	gi->playerCustomInfo.dinoMeshNum = 1;

	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType3()
{
	gi->playerCustomInfo.dinoMeshNum = 2;

	player->SetMesh();
}

void UJE_TypeListViewWidget::OnClickedType4()
{
	gi->playerCustomInfo.dinoMeshNum = 3;

	player->SetMesh();
}
