// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH_NetPlayerController.h"
#include "Components/WidgetComponent.h"
#include "JE_NicknameWidget.h"
#include "BlueTrex.h"
#include "Components/TextRenderComponent.h"

ALSH_NetPlayerController::ALSH_NetPlayerController()
{
	//PrimaryActorTick.bCanEverTick = true;

	//APawn* player = GetPawn();

	//if (player)
	//{
	//	// 닉네임 컴포넌트 생성
	//	nickNameComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("nickNameComp"));
	//	nickNameComp->SetupAttachment(player->GetRootComponent());
	//	nickNameComp->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	//	nickNameComp->SetWidgetSpace(EWidgetSpace::Screen);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NicknameUI"));
	//}

	
}

void ALSH_NetPlayerController::BeginPlay()
{
    Super::BeginPlay();

	bluePlayer = Cast<ABlueTrex>(GetPawn());

	/*if (bluePlayer != nullptr)
	{
		bluePlayer->nicknameText->SetVisibility(true);
	}*/

	/*if (nickNameComp != nullptr)
	{
		nickNameComp->AttachToComponent(player->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), "HeadSocket");
		nickNameUI = Cast<UJE_NicknameWidget>(nickNameComp->GetWidget());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NicknameUI"));
	}*/

	//if (player)
	//{
	//	nickNameComp->AttachToComponent(player->GetRootComponent());
	//}
}
