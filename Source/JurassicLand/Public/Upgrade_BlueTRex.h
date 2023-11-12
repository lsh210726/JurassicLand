// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "Upgrade_BlueTRex.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API AUpgrade_BlueTRex : public ABasePlayer
{
	GENERATED_BODY()
	
	AUpgrade_BlueTRex();
public:	
	class UAnimInstance* ABP_TRex;
};
