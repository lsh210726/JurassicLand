// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetGameInstance.h"
#include "OnlineSubsystem.h"
//#include "OnlineSessionInterface.h"

ULSH_NetGameInstance::ULSH_NetGameInstance()
{
	mySessionName = TEXT("netTester1");
}

void ULSH_NetGameInstance::Init()
{
	Super::Init();

	//if (IOnlineSubsystem* subsys = IOnlineSubsystem::Get())
	//{

	//}
}
