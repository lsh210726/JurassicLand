// Fill out your copyright notice in the Description page of Project Settings.


#include "DragDropWidget.h"
#include "Kismet/GameplayStatics.h"

void UDragDropWidget::NativeConstruct()
{

	player = Cast<ACT_CameraCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(player == nullptr) return;

}
