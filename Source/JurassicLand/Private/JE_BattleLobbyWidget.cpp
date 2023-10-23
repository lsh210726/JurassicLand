// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleLobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UJE_BattleLobbyWidget::NativeConstruct()
{
	btn_mapchoice->OnClicked.AddDynamic(this, &UJE_BattleLobbyWidget::OnClickedChoice);
	btn_mapcheck->OnClicked.AddDynamic(this, &UJE_BattleLobbyWidget::OnClickedCheck);

}

void UJE_BattleLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_BattleLobbyWidget::OnClickedCheck()
{
	SwitchLobbyCanvas(2);
}

void UJE_BattleLobbyWidget::OnClickedChoice()
{
	SwitchLobbyCanvas(1);
}

void UJE_BattleLobbyWidget::SwitchLobbyCanvas(int32 index)
{
	ws_BattleLobbyUI->SetActiveWidgetIndex(index);
}
