// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_TypeListViewWidget.h"
#include "LSH_NetGameInstance.h"
#include "Components/Button.h"
#include "BlueTrex.h"

void UJE_TypeListViewWidget::NativeConstruct()
{
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
	
}

void UJE_TypeListViewWidget::OnClickedType2()
{

}

void UJE_TypeListViewWidget::OnClickedType3()
{

}

void UJE_TypeListViewWidget::OnClickedType4()
{

}
