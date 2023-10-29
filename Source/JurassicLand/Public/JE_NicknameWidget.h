// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JE_NicknameWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API UJE_NicknameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	class ULSH_NetGameInstance* gi;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category=MySettings)
	class UTextBlock* txt_playerName;
	
	
};
