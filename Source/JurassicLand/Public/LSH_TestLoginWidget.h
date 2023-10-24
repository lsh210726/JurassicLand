// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LSH_TestLoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API ULSH_TestLoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget),Category=MySettings)
	class UEditableText* edit_MyName;

	class ULSH_NetGameInstance* gi;

	UFUNCTION()
	void CreateSession();
	UFUNCTION()
	void FindSession();
};
