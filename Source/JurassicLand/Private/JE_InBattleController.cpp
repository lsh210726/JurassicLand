// Fill out your copyright notice in the Description page of Project Settings.


#include "JE_InBattleController.h"
#include "JE_NicknameWidget.h"
#include "BlueTrex.h"
#include "JE_BattleLobbyGameMode.h"
#include "Raptor.h"
#include "LSH_NetGameInstance.h"


AJE_InBattleController::AJE_InBattleController()
{

}

void AJE_InBattleController::BeginPlay()
{
	Super::BeginPlay();

	ABlueTrex* bluePlayer = Cast<ABlueTrex>(GetPawn());

	ULSH_NetGameInstance* gi = GetGameInstance<ULSH_NetGameInstance>();

	if (gi->playerCustomInfo.dinoMeshNum == 1)
	{
		if (HasAuthority())
		{
			AJE_BattleLobbyGameMode* gm = GetWorld()->GetAuthGameMode<AJE_BattleLobbyGameMode>();

			ABlueTrex* trex = Cast<ABlueTrex>(GetPawn());
			UnPossess();

			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


			ARaptor* playerRaptor = GetWorld()->SpawnActor<ARaptor>(gi->raptor, FVector((760.0f, -500.0f, 1000.0f)), FRotator(), param);

			if (playerRaptor)
			{
				Possess(playerRaptor);
			}

			if (trex) trex->Destroy();

		}
	}
}