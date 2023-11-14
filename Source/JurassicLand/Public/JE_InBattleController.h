// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JE_InBattleController.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API AJE_InBattleController : public APlayerController
{
	GENERATED_BODY()

public:

	AJE_InBattleController();

protected:
	virtual void BeginPlay() override;
	
};
