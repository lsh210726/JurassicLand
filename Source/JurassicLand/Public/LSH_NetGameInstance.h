// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LSH_NetGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JURASSICLAND_API ULSH_NetGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	ULSH_NetGameInstance();

	virtual void Init() override;

	UPROPERTY()
	FString mySessionName;

	IOnlineSessionPtr sessionInterface;

	void CreateMySession();//세션만들기함수

	void OncreatedMySession(FName sessionName, bool bWasSuccessful);//세션이 만들어지고 난후 실행될 델리케이트 함수
};
