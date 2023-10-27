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
		//Online Session Interface API ���ٿ� �ν��Ͻ� ��������
		sessionInterface = subsys->GetSessionInterface();

		//���� �̺�Ʈ�� �Լ� ���ε��ϱ�
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OncreatedMySession);
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OnFindOtherSessions);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ULSH_NetGameInstance::OnJoinSelectedSession);

	}
}

void ULSH_NetGameInstance::CreateMySession(FText username)
{	
	FOnlineSessionSettings sessionSettings;//���Ǽ��� ����, ����ü
	//1. lan�������� dedicated�������� ����
	sessionSettings.bIsDedicated = false;//�������� ����
	sessionSettings.bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == FName("Null");//����İ� ��������� ���� > ������ ����
	UE_LOG(LogTemp, Warning, TEXT("%s"),*IOnlineSubsystem::Get()->GetSubsystemName().ToString());
	//2. �˻������� ������ �����ϱ�
	sessionSettings.bShouldAdvertise = true;

	//3. �ڱ� ������ ���޵� �� �ְ� �����ϱ�
	sessionSettings.bUsesPresence = true;

	//4. �ٸ������� �߰� ���� ����ϱ�
	sessionSettings.bAllowJoinInProgress = true;
	sessionSettings.bAllowJoinViaPresence = true;//������ ���� ������ �ƴ� ģ�� ���� ���� ��

	//5. ���� ���� �ο��� �����Ѵ�
	sessionSettings.NumPublicConnections = 2;

	//6. ���ǿ� �߰� ������ �ִ´�
	sessionSettings.Set(FName("Room_Name"), username.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	myName = username.ToString();

	bool isSuccess = sessionInterface->CreateSession(0, FName(myName), sessionSettings);//���̸�, �漼��
	UE_LOG(LogTemp, Warning, TEXT("Session Create Result : %s"), isSuccess ? *FString("Success") : *FString("Failed"));


}

void ULSH_NetGameInstance::OncreatedMySession(FName sessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		FString mapAdress = "/Game/LSH_WorkSpace/LSH_BattleMap";//�̵��� �� �ּ�
		bool travelResult = GetWorld()->ServerTravel(mapAdress+"?Listen", true);//�ּ�+���� ���� ��ü ���������ν� �̵�, �ɸ��� Ȥ�� �ۼַ�Ʈ ó���� ������ �ۼַ�Ʈ//����Ʈ������ ȣ��Ʈ�� ��� �����ϴ� > ������ �ְ� Ʈ������ �ϸ� �ڽ����� �پ� �ִ� ��� Ŭ���̾�Ʈ���� ��� ������ ���̵��Ѵ�. Ŭ���̾�ƮƮ������ �ڱ⸸ �̵��Ѵ�. ȣ��Ʈ�� �и� �� ������ �������� ������ �� ���. ����Ʈ������ �����忡 ����, Ŭ���̾�ƮƮ������ �÷��̾���Ʈ�ѷ��� ������
		UE_LOG(LogTemp, Warning, TEXT("travel Result : %s"), travelResult ? *FString("Success") : *FString("Failed"));

	}
}

void ULSH_NetGameInstance::FindOtherSession()
{
	sessionSearch = MakeShareable(new FOnlineSessionSearch());

	//1. ���� �˻��� lan���� �� ������ �����Ѵ�
	sessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == FName("Null");
	//2. ���� ���� ����
	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	//3. ������ �˻����� ����
	sessionSearch->MaxSearchResults = 3;

	sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
}

void ULSH_NetGameInstance::OnFindOtherSessions(bool bWasSyccessful)
{
	if (bWasSyccessful)
	{
		//�˻��� ���� ����� �����´�
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;
		sessionNum = searchResults.Num();
		UE_LOG(LogTemp, Warning, TEXT("Find Session %d"),sessionNum );
		for (auto result : searchResults)
		{
			FString username;
			result.Session.SessionSettings.Get(FName("Room_Name"), username);
			int32 openNumber = result.Session.NumOpenPublicConnections;//�����ڸ���ȸ
			int32 maxNumber = result.Session.SessionSettings.NumPublicConnections;//��ü�ڸ���ȸ
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
	sessionInterface->JoinSession(0, FName(myName), sessionSearch->SearchResults[0]);//���� ���� ���ǿ� ����
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
						FString url;//join�� ���� ȣ��Ʈ�� ����Ʈ������ �� �ּҸ� �޾ƿ´�
						sessionInterface->GetResolvedConnectString(sessionName,url);
						UE_LOG(LogTemp, Warning, TEXT("connection url %s"), *url);
						//�ּҸ� �޾Ҵٸ� �� �ּҿ� ���� �� �̵��Ѵ�
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

void ULSH_NetGameInstance::OnTravlebattleMap()
{
	FString mapAdress = "/Game/1_Level/BattleOpenMap";//�̵��� �� �ּ�
	bool travelResult = GetWorld()->ServerTravel(mapAdress + "?Listen", true);//�ּ�+���� ���� ��ü ���������ν� �̵�, �ɸ��� Ȥ�� �ۼַ�Ʈ ó���� ������ �ۼַ�Ʈ//����Ʈ������ ȣ��Ʈ�� ��� �����ϴ� > ������ �ְ� Ʈ������ �ϸ� �ڽ����� �پ� �ִ� ��� Ŭ���̾�Ʈ���� ��� ������ ���̵��Ѵ�. Ŭ���̾�ƮƮ������ �ڱ⸸ �̵��Ѵ�. ȣ��Ʈ�� �и� �� ������ �������� ������ �� ���. ����Ʈ������ �����忡 ����, Ŭ���̾�ƮƮ������ �÷��̾���Ʈ�ѷ��� ������
	/*APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	playerCon->ClientTravel(mapAdress, ETravelType::TRAVEL_Absolute);*/
	
	UE_LOG(LogTemp, Warning, TEXT("travel Result : %s"), travelResult ? *FString("Success") : *FString("Failed"));
}
