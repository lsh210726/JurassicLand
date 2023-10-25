// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_MultiBattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "LSH_NetGameInstance.h"

void UJE_MultiBattleWidget::NativeConstruct()
{
	gi = GetGameInstance<ULSH_NetGameInstance>();

	btn_ready->OnClicked.AddDynamic(this, &UJE_MultiBattleWidget::OnClickedReady);

}

void UJE_MultiBattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_MultiBattleWidget::OnClickedReady()
{
	if(readyCount == 0)
		readyCount++;
	
	FString Message = FString::Printf(TEXT("%d"), readyCount);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

}
