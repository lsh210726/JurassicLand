// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_GameStartWidget.h"
#include "JE_GI.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "LSH_NetGameInstance.h"
#include "BlueTrex.h"



void UJE_GameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//je_gi = GetGameInstance<UJE_GI>();
	gi = GetGameInstance<ULSH_NetGameInstance>();
	player = GetOwningPlayerPawn<ABlueTrex>();

	txt_coin->SetText(FText::AsNumber(player->currentCoin));

	btn_skip->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedSkip);
	btn_play->OnHovered.AddDynamic(this, &UJE_GameStartWidget::OnHoveredPlay);
	btn_play->OnUnhovered.AddDynamic(this, &UJE_GameStartWidget::OnUnHoveredBattle);
	btn_battle->OnHovered.AddDynamic(this, &UJE_GameStartWidget::OnHoveredBattle);
	btn_battle->OnUnhovered.AddDynamic(this, &UJE_GameStartWidget::OnUnHoveredBattle);
	btn_battle->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedBattle);
	btn_nickCheck->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedNickCheck);

	btn_custom->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedCustom);



}

void UJE_GameStartWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (currentTime < endTime)
	{
		currentTime += InDeltaTime;

		pb_loading->SetPercent(currentTime / endTime);
	}
	else
	{
		if(loadingCount == 0)
		{
			SwitchCanvas(1);
			loadingCount++;
		}
		else
		{
			return;
		}
	}

}

void UJE_GameStartWidget::OnClickedSkip()
{
	//FString Message = FString::Printf(TEXT("SkipButtonClicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	
	SwitchCanvas(2);
}

void UJE_GameStartWidget::OnClickedNickCheck()
{
	if (!edit_nickname->GetText().IsEmpty())
	{
		gi->myName = edit_nickname->GetText().ToString();
		gi->playerCustomInfo.dinoName = edit_nickname->GetText().ToString();
	}
	
	SwitchCanvas(3);

}

void UJE_GameStartWidget::OnHoveredPlay()
{
	btn_battle->SetVisibility(ESlateVisibility::Visible);
}

void UJE_GameStartWidget::OnHoveredBattle()
{
	btn_battle->SetVisibility(ESlateVisibility::Visible);
}

void UJE_GameStartWidget::OnUnHoveredBattle()
{
	if (btn_battle->GetVisibility() == ESlateVisibility::Visible)
	{
		/*FTimerHandle initHandler;
		GetWorld()->GetTimerManager().SetTimer(initHandler, FTimerDelegate::CreateLambda([&]() {
			btn_battle->SetVisibility(ESlateVisibility::Hidden);
			}), 1.0f, false);*/
		btn_battle->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UJE_GameStartWidget::OnClickedBattle()
{
	//FString Message = FString::Printf(TEXT("SkipButtonClicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	FString LevelName = TEXT("MainMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void UJE_GameStartWidget::OnClickedCustom()
{
	FString Message = FString::Printf(TEXT("custom"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	FString LevelName = TEXT("CustomMap");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}

void UJE_GameStartWidget::SwitchCanvas(int32 index)
{
	ws_GameStartUI->SetActiveWidgetIndex(index);
}
