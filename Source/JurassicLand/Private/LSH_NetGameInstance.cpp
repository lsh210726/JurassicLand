// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

ULSH_NetGameInstance::ULSH_NetGameInstance()
{
	mySessionName = TEXT("netTester1");
}

void ULSH_NetGameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	{
		//Online Session Interface API 접근용 인스턴스 가져오기
		sessionInterface = subsys->GetSessionInterface();

		//세션 이벤트에 함수 바인딩하기
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OncreatedMySession);
		FTimerHandle createHandler;
		GetWorld()->GetTimerManager().SetTimer(createHandler, this, &ULSH_NetGameInstance::CreateMySession, 0.1, false);//1초 뒤에 실행되게
	}
}

void ULSH_NetGameInstance::CreateMySession()
{	
	FOnlineSessionSettings sessionSettings;//세션세팅 선언, 구조체
	//1. lan연결인지 dedicated연결인지 설정
	sessionSettings.bIsDedicated = false;//리슨서버 설정
	sessionSettings.bIsLANMatch = true;//랜방식과 스팀방식의 차이 > 스팀은 원격
	//2. 검색가능한 방으로 설정하기
	sessionSettings.bShouldAdvertise = true;

	//3. 자기 정보를 전달될 수 있게 설정하기
	sessionSettings.bUsesPresence = true;

	//4. 다른유저의 중간 입장 허용하기
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;//광고를 통한 난입이 아닌 친구 따라서 들어올 때

	//5. 입장 가능 인원을 설정한다
	sessionSettings.NumPublicConnections = 10;


	bool isSuccess = sessionInterface->CreateSession(0, FName("TestRoom"), sessionSettings);//방이름, 방세팅
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));


}

void ULSH_NetGameInstance::OncreatedMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		FString mapAdress = "/Game/LSH_WorkSpace/LSH_BattleMap";//이동할 맵 주소
		bool travelResult = GetWorld()->ServerTravel(mapAdress+"?Listen", true);//주소+내가 서버 주체 리슨서버로써 이동, 심리스 혹은 앱솔루트 처음은 무조건 앱솔루트//서버트래블은 호스트만 사용 가능하다 > 서버인 애가 트래블은 하면 자신한테 붙어 있는 모든 클라이언트들을 모두 데리고 맵이동한다. 클라이언트트레블은 자기만 이동한다. 호스트와 분리 시 세션이 없어진다 조인할 때 사용. 서버트레블은 유월드에 구현, 클라이언트트레블은 플레이어컨트롤러에 구현됨
		UE_LOG(LogTemp, Warning, TEXT("travel Result : %s"), travelResult ? *FString("Success") : *FString("Failed"));

	}
}
