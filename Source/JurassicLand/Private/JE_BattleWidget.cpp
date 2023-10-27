// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UJE_BattleWidget::NativeConstruct()
{
	FTimerHandle initHandler;
	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::LoadingUI, 3.0f, false);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_BattleWidget::LoadingUI()
{
	ws_Battle->SetActiveWidgetIndex(1);
	PlayAnimation(battleStartAnim);

	FTimerHandle loadingHandler;
	GetWorld()->GetTimerManager().SetTimer(loadingHandler, FTimerDelegate::CreateLambda([&]() {
		
		ws_Battle->SetActiveWidgetIndex(2);

		}), 2.0f, false);

}

void UJE_BattleWidget::StartUIAnim()
{
	
}
