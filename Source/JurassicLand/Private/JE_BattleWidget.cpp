// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Animation/WidgetAnimation.h"
#include "BlueTrex.h"

void UJE_BattleWidget::NativeConstruct()
{
	//battleStartAnim = UKismetWidgetBlueprintLibrary::GetAnimationByName(TEXT("battleStartAnim"));

	player = GetOwningPlayerPawn<ABlueTrex>();

	FTimerHandle initHandler;
	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::LoadingUI, 3.0f, false);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (player->TRexHP <= 0.0f)
	{
		ws_Battle->SetActiveWidgetIndex(2);
		txt_battleresult->SetText(FText::FromString("Win"));
	}
}

void UJE_BattleWidget::LoadingUI()
{
	StartUIAnim();

	FTimerHandle loadingHandler;
	GetWorld()->GetTimerManager().SetTimer(loadingHandler, FTimerDelegate::CreateLambda([&]() {
		
		ws_Battle->SetActiveWidgetIndex(2);
		//player->GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());

		}), 2.0f, false);

}

void UJE_BattleWidget::StartUIAnim()
{
	ws_Battle->SetActiveWidgetIndex(1);

	FTimerHandle AnimHandler;
	GetWorld()->GetTimerManager().SetTimer(AnimHandler, FTimerDelegate::CreateLambda([&]() {

		PlayAnimationForward(battleStartAnim);

		}), 0.2f, false);
}
