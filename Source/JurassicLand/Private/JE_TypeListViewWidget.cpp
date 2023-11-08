// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_TypeListViewWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"

void UJE_TypeListViewWidget::NativeConstruct()
{
	btn_type->OnClicked.AddDynamic(this, &UJE_TypeListViewWidget::OnClickedType);
}

void UJE_TypeListViewWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_TypeListViewWidget::OnClickedType()
{

}
