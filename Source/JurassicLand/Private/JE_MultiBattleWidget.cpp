// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_MultiBattleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "LSH_NetGameInstance.h"
#include "Net/UnrealNetwork.h"


void UJE_MultiBattleWidget::NativeConstruct()
{
	gi = GetGameInstance<ULSH_NetGameInstance>();

	btn_ready->OnClicked.AddDynamic(this, &UJE_MultiBattleWidget::OnClickedReady);

}

void UJE_MultiBattleWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UJE_MultiBattleWidget::OnClickedReady()
{
	//if (clickOnce)
	//{
	//	readyCount++;
	//	clickOnce = false;
	//}

	//FString Message = FString::Printf(TEXT("%d"), readyCount);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
	//UE_LOG(LogTemp, Warning, TEXT("readycount %d , %d"), readyCount, clickOnce);
	if (clickOnce)
	{
		clickOnce = false;
		serverReadyCountUp();
	}
	UE_LOG(LogTemp, Warning, TEXT("readycount %d , %d"), readyCount, clickOnce);
}

void UJE_MultiBattleWidget::serverReadyCountUp_Implementation()
{

	readyCount++;


	UE_LOG(LogTemp, Warning, TEXT("readycount %d , %d"), readyCount, clickOnce);
}
