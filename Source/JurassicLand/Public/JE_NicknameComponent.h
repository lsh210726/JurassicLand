// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JE_NicknameComponent.generated.h"


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JURASSICLAND_API UJE_NicknameComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJE_NicknameComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 닉네임 ui 파일
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UUserWidget> nickNameWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	class UUserWidget* nickNameUI;

		
};
