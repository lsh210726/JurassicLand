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

	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::StartUIAnim, 1.0f, false);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//FString Message = FString::Printf(TEXT("%d"), ws_Battle->GetActiveWidgetIndex());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	//
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
	//GetWorld()->GetTimerManager().ClearTimer(initHandler);
	ws_Battle->SetActiveWidgetIndex(1);
	PlayAnimationForward(startText);

	FTimerHandle AnimHandler;
	GetWorld()->GetTimerManager().SetTimer(AnimHandler, FTimerDelegate::CreateLambda([&]() {

		
		FString Message = FString::Printf(TEXT("startUIANim"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);


		}), 0.1f, false);
}
