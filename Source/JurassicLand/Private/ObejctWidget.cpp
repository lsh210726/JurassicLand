// Fill out your copyright notice in the Description page of Project Settings.


#include "ObejctWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CreateObject.h"
#include "Components/Image.h"



UObejctWidget::UObejctWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DetectDragKey = EKeys::LeftMouseButton;
}

void UObejctWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	//Img_object->OnDragCancelled.AddDynamic(this, &UObejctWidget::OnDragCancelled);
}

FReply UObejctWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FReply Local_Reply = Super::OnMouseButtonDown(InGeometry, InMouseEvent).NativeReply;
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, DetectDragKey).NativeReply;
}

//FEventReply UObejctWidget::NativeOnMouseButtonDown(FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
//{
//	FEventReply Reply = Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);
//
//	return Reply;
//}



void UObejctWidget::NativeOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent, UDragDropOperation*& Operation)
{
	Super::NativeOnDragDetected(MyGeometry, PointerEvent, Operation);
	/*Super::NativeOnDragDetected(MyGeometry, PointerEvent, Operation);

	if (objectWidget)
	{
		objectWidgetRef = CreateWidget<UObejctWidget>(this, objectWidget);
		if (objectWidgetRef)
		{
			objectWidgetRef->SetOwningPlayer(GetOwningPlayer());
		}
	}*/

	Operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	objectWidgetRef = CreateWidget<UObejctWidget>(GetWorld(), objectWidget);

	Operation->Payload = objectWidgetRef;
	Operation->DefaultDragVisual = objectWidgetRef;
	Operation->Pivot = EDragPivot::CenterCenter;


}

void UObejctWidget::NativeOnDragCancelled(const FDragDropEvent& PointerEvent, UDragDropOperation* Operation)
{
	Super::NativeOnDragCancelled(PointerEvent, Operation);
	
	FVector2D mousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FVector worldPos;
	FVector worldDir;

	UGameplayStatics::DeprojectScreenToWorld(GetOwningPlayer(), mousePosition * UWidgetLayoutLibrary::GetViewportScale(this->GetWorld()), worldPos, worldDir);

	FHitResult hitInfo;
	if (GetWorld()->LineTraceSingleByChannel(hitInfo, worldPos, worldPos + worldDir * 2000.0f, ECC_Visibility))
	{
		GetWorld()->SpawnActor<ACreateObject>(ACreateObject::StaticClass(), hitInfo.Location, FRotator::ZeroRotator);
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hit"));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("NoHit"));
	}

	
}
