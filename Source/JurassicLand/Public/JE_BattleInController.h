// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JE_BattleInController.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API AJE_BattleInController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;	
	
};
