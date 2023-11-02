// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_CustomItemWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "JE_CustomItem.h"



void UJE_CustomItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//static ConstructorHelpers::FObjectFinder<UDataTable> tmpDataTable(TEXT("/Game/7_MISC/ItemData/CustomItems.CustomItems"));
// 	if (tmpDataTable.Succeeded())
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
// 		CustomItemTable = tmpDataTable.Object;
// 
// 	}

	/*for (int i = 0; i < 3; i++)
	{
		UButton* buttonHat =CreateDefaultSubobject<UButton>(TEXT("buttonHat"));
	}*/

	btn_Tab_Hat->OnClicked.AddDynamic(this, &UJE_CustomItemWidget::OnClickedTabHat);
	btn_Tab_Glasses->OnClicked.AddDynamic(this, &UJE_CustomItemWidget::OnClickedTabGlasses);
	btn_Tab_Shoes->OnClicked.AddDynamic(this, &UJE_CustomItemWidget::OnClickedTabShoes);
}

void UJE_CustomItemWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UJE_CustomItemWidget::OnClickedTabHat()
{
	ws_CustomItem->SetActiveWidgetIndex(0);
}

void UJE_CustomItemWidget::OnClickedTabGlasses()
{
	ws_CustomItem->SetActiveWidgetIndex(1);

}

void UJE_CustomItemWidget::OnClickedTabShoes()
{
	ws_CustomItem->SetActiveWidgetIndex(2);

}

void UJE_CustomItemWidget::SetButtonImage(UButton* btn)
{

}
