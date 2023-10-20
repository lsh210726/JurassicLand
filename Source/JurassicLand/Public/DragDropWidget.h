// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CT_CameraCharacter.h"
#include "DragDropWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UDragDropWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ACT_CameraCharacter* player;

public:	
	void NativeConstruct() override;
	
};
