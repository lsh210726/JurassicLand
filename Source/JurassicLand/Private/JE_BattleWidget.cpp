// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Animation/WidgetAnimation.h"
#include "BlueTrex.h"

void UJE_BattleWidget::NativeConstruct()
{

	Super::NativeConstruct();

	//battleStartAnim = UKismetWidgetBlueprintLibrary::GetAnimationByName(TEXT("battleStartAnim"));

	player = GetOwningPlayerPawn<ABlueTrex>();

	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::StartUIAnim, 5.0f, false);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FString Message = FString::Printf(TEXT("%d"), player->TRexHP);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

	if (player->TRexHP <= 0.f)
	{
		ws_Battle->SetActiveWidgetIndex(3);
		txt_battleresult->SetText(FText::FromString("Lose"));

	}


}

void UJE_BattleWidget::LoadingUI()
{
	ws_Battle->SetActiveWidgetIndex(2);
}

void UJE_BattleWidget::StartUIAnim()
{
	ws_Battle->SetActiveWidgetIndex(1);
	PlayAnimationForward(startText);

	FTimerHandle AnimHandler;
	GetWorld()->GetTimerManager().SetTimer(AnimHandler, FTimerDelegate::CreateLambda([&]() {

		
		FString Message = FString::Printf(TEXT("startUIANim"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
		LoadingUI();

		}), 3.0f, false);
}
