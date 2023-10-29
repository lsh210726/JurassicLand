// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_BattleLobbyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "LSH_NetGameInstance.h"
#include "BlueTrex.h"


void UJE_BattleLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	//GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, gi->myName);

	btn_battleIn->OnClicked.AddDynamic(this, &UJE_BattleLobbyWidget::OnClickedbattleIn);
	//txt_coin_battle->SetText(FText::AsNumber(player->currentCoin));

}

void UJE_BattleLobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	txt_coin_battle->SetText(FText::AsNumber(player->currentCoin));
}

void UJE_BattleLobbyWidget::OnClickedbattleIn()
{
	//FString Message = FString::Printf(TEXT("SkipButtonClicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Click"));
	gi = GetGameInstance<ULSH_NetGameInstance>();

	FTimerHandle findHandler;
	GetWorld()->GetTimerManager().SetTimer(findHandler, this, &UJE_BattleLobbyWidget::battleFindSession, 0.1, false);
	
	FTimerHandle eTimerHandle;
	float etime = 10;

	GetWorld()->GetTimerManager().SetTimer(eTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 코드 구현

			if (gi->sessionNum >= 99 || gi->sessionNum <= 0)
			{
				//FTimerHandle createHandler2;

				//GetWorld()->GetTimerManager().SetTimer(createHandler2, this, &ULSH_TestLoginWidget::CreateSession, 3, false);//1초 뒤에 실행되게
				//gi->CreateMySession(FText::FromString("Player"));
				gi->CreateMySession(FText::FromString(gi->myName));

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("join session"));
				gi->JoinOtherSession();

			}
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(eTimerHandle);
			widgetIndex = 1;
			//SwitchLobbyCanvas(widgetIndex);

		}), etime, false);	// 반복하려면 false를 true로 변경



}

void UJE_BattleLobbyWidget::battleFindSession()
{
	UE_LOG(LogTemp, Warning, TEXT("FindSession"));
	if (gi != nullptr)
	{
		gi->FindOtherSession();
	}
}

void UJE_BattleLobbyWidget::SwitchLobbyCanvas(int32 index)
{
	ws_BattleLobbyUI->SetActiveWidgetIndex(index);
}
