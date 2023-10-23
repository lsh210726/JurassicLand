// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleLobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UJE_BattleLobbyWidget::NativeConstruct()
{
	btn_battleIn->OnClicked.AddDynamic(this, &UJE_BattleLobbyWidget::OnClickedbattleIn);
}

void UJE_BattleLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_BattleLobbyWidget::OnClickedbattleIn()
{
	SwitchLobbyCanvas(1);
}

void UJE_BattleLobbyWidget::SwitchLobbyCanvas(int32 index)
{
	ws_BattleLobbyUI->SetActiveWidgetIndex(index);
}
