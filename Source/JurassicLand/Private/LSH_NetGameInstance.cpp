// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

ULSH_NetGameInstance::ULSH_NetGameInstance()
{
	myName = TEXT("netTester1");
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
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OnFindOtherSessions);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OnJoinSelectedSession);

	}
}

void ULSH_NetGameInstance::CreateMySession(FText username)
{	
	FOnlineSessionSettings sessionSettings;//세션세팅 선언, 구조체
	//1. lan연결인지 dedicated연결인지 설정
	sessionSettings.bIsDedicated = false;//리슨서버 설정
	sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("Null");//랜방식과 스팀방식의 차이 > 스팀은 원격
	UE_LOG(LogTemp, Warning, TEXT("%s"),*IOnlineSubsystem::Get()->GetSubsystemName().ToString());
	//2. 검색가능한 방으로 설정하기
	sessionSettings.bShouldAdvertise = true;

	//3. 자기 정보를 전달될 수 있게 설정하기
	sessionSettings.bUsesPresence = true;

	//4. 다른유저의 중간 입장 허용하기
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;//광고를 통한 난입이 아닌 친구 따라서 들어올 때

	//5. 입장 가능 인원을 설정한다
	sessionSettings.NumPublicConnections = 2;

	//6. 세션에 추가 설정을 넣는다
	sessionSettings.Set(FName("Room_Name"), username.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	myName = username.ToString();

	bool isSuccess = sessionInterface->CreateSession(0, FName(myName), sessionSettings);//방이름, 방세팅
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

void ULSH_NetGameInstance::FindOtherSession()
{
	sessionSearch = MakeShareable(new FOnlineSessionSearch());

	//1. 세션 검색을 lan으로 할 것인지 설정한다
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == FName("Null");
	//2. 세션 쿼리 설정
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	//3. 세션의 검색량을 설정
	sessionSearch->MaxSearchResults = 3;

	sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void ULSH_NetGameInstance::OnFindOtherSessions(bool bWasSyccessful)
{
	if (bWasSyccessful)
	{
		//검색된 세션 목록을 가져온다
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;
		sessionNum = searchResults.Num();
		UE_LOG(LogTemp, Warning, TEXT("Find Session %d"),sessionNum );
		for (auto result : searchResults)
		{
			FString username;
			result.Session.SessionSettings.Get(FName("Room_Name"), username);
			int32 openNumber = result.Session.NumOpenPublicConnections;//남은자리조회
			int32 maxNumber = result.Session.SessionSettings.NumPublicConnections;//전체자리조회
			int32 pingSpeed = result.PingInMs;

			UE_LOG(LogTemp, Warning, TEXT("roomname %s, opennumber %d/%d, pingspeed %d"), *username, openNumber, maxNumber, pingSpeed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("session find fail"));
	}
}

void ULSH_NetGameInstance::JoinOtherSession()
{
	sessionInterface->JoinSession(0, FName(myName), sessionSearch->SearchResults[0]);//제일 위의 세션에 접속
}

void ULSH_NetGameInstance::OnJoinSelectedSession(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), result == EOnJoinSessionCompleteResult::Success ? *FString("success") : *FString(TEXT("Failed")));
	switch (result)
	{
	case EOnJoinSessionCompleteResult::Success:
		{
			UE_LOG(LogTemp, Warning, TEXT("Success %s"), *sessionName.ToString());
	
					APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
					if (playerCon != nullptr)
					{
						FString url;//join된 세션 호스트의 서버트레블된 맵 주소를 받아온다
						sessionInterface->GetResolvedConnectString(sessionName,url);
						UE_LOG(LogTemp, Warning, TEXT("connection url %s"), *url);
						//주소를 받았다면 그 주소에 따라서 맵 이동한다
						if(!url.IsEmpty()) playerCon->ClientTravel(url,ETravelType::TRAVEL_Absolute);
					}
		}
		break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		UE_LOG(LogTemp, Warning, TEXT("SessionIsFull"));
		break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		UE_LOG(LogTemp, Warning, TEXT("SessionDoesNotExist"));
		break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		UE_LOG(LogTemp, Warning, TEXT("CouldNotRetrieveAddress"));
		break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		UE_LOG(LogTemp, Warning, TEXT("AlreadyInSession"));
		break;
	case EOnJoinSessionCompleteResult::UnknownError:
		UE_LOG(LogTemp, Warning, TEXT("UnknownError"));
		break;
	default:
		break;
	}
}
