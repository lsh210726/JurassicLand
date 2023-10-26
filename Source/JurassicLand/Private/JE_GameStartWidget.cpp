// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_GameStartWidget.h"
#include "JE_GI.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"



void UJE_GameStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	je_gi = GetGameInstance<UJE_GI>();


	currentCoin = initialCoin;
	txt_coin->SetText(FText::AsNumber(currentCoin));

	btn_skip->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedSkip);
	btn_play->OnHovered.AddDynamic(this, &UJE_GameStartWidget::OnHoveredPlay);
	btn_play->OnUnhovered.AddDynamic(this, &UJE_GameStartWidget::OnUnHoveredBattle);
	btn_battle->OnHovered.AddDynamic(this, &UJE_GameStartWidget::OnHoveredBattle);
	btn_battle->OnUnhovered.AddDynamic(this, &UJE_GameStartWidget::OnUnHoveredBattle);
	btn_battle->OnClicked.AddDynamic(this, &UJE_GameStartWidget::OnClickedBattle);



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

void UJE_GameStartWidget::SwitchCanvas(int32 index)
{
	ws_GameStartUI->SetActiveWidgetIndex(index);
}
