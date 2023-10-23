// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObejctWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UObejctWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = MySettings)
	class UImage* Img_object;

	UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> objectWidget;

	UObejctWidget* objectWidgetRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	FKey DetectDragKey;
	
public:	

	UObejctWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent, UDragDropOperation*& Operation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& PointerEvent, UDragDropOperation* Operation) override;
};
