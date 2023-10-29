// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Animation/WidgetAnimation.h"
#include "BlueTrex.h"
#include "LSH_NetGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "JE_BattleInController.h"

void UJE_BattleWidget::NativeConstruct()
{

	Super::NativeConstruct();

	//battleStartAnim = UKismetWidgetBlueprintLibrary::GetAnimationByName(TEXT("battleStartAnim"));

	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();
	//pc = GetOwningPlayer<AJE_BattleInController>();

	player->bIsHPShow = true;

	GetWorld()->GetTimerManager().SetTimer(initHandler, this, &UJE_BattleWidget::StartUIAnim, 5.0f, false);

	btn_toMain->OnClicked.AddDynamic(this, &UJE_BattleWidget::OnClickedToMain);
}

void UJE_BattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//FString Message = gi->isEnd == true ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);

	if (gi->isEnd && !ischange)
	{
		if (player->TRexHP <= 0.f)
		{
			ws_Battle->SetActiveWidgetIndex(3);
			txt_battleresult->SetText(FText::FromString("Lose"));
			GetWorld()->GetTimerManager().SetTimer(CoinHandler, this, &UJE_BattleWidget::CoinUI, 5.0f, false);

			ischange = true;

		}
		else
		{
			ws_Battle->SetActiveWidgetIndex(3);
			txt_battleresult->SetText(FText::FromString("Win"));
			player->currentCoin += 5000.f;
			GetWorld()->GetTimerManager().SetTimer(CoinHandler, this, &UJE_BattleWidget::CoinUI, 5.0f, false);

			ischange = true;

		}

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

		
		//FString Message = FString::Printf(TEXT("startUIANim"));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
		LoadingUI();

		}), 3.0f, false);
}

void UJE_BattleWidget::CoinUI()
{
	ws_Battle->SetActiveWidgetIndex(4);
	bisMouse = true;
	/*if (pc)
	{
		FInputModeGameAndUI InputMode;
		pc->SetInputMode(InputMode);
		pc->bShowMouseCursor = true;
	}*/

}

void UJE_BattleWidget::OnClickedToMain()
{
	FString LevelName = TEXT("MainMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}
