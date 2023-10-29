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
	FString myName;
	int32 sessionNum = 99;

	IOnlineSessionPtr sessionInterface;
	TSharedPtr<FOnlineSessionSearch> sessionSearch;

	void CreateMySession(FText userName);//세션만들기함수
	void OncreatedMySession(FName sessionName, bool bWasSuccessful);//세션이 만들어지고 난후 실행될 델리케이트 함수
	void FindOtherSession();//다른사람이만들어놓은세션검색함수
	void OnFindOtherSessions(bool bWasSyccessful);//세션 찾으면 바인딩 함수
	void JoinOtherSession();
	void OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result);
	void OnTravlebattleMap();//게임 시작버튼 눌렀을 때 서버트래블

public:
	UPROPERTY()
	bool isEnd = false;
};
