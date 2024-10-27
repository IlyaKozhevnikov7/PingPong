// Fill out your copyright notice in the Description page of Project Settings.

#include "PPGameMode.h"
#include "PPGameStateBase.h"
#include "PPArena.h"
#include "PPPlayerState.h"

void APPGameMode::PostLogin(APlayerController* newPlayer)
{
	Super::PostLogin(newPlayer);

	Arena->AddPlayer(newPlayer);
}

void APPGameMode::SetArena(APPArena* arena)
{
	if (Arena == nullptr && arena != nullptr)
	{
		Arena = arena;
	}
}

void APPGameMode::AddPoint(APlayerController* controller)
{
	auto playerState = controller->GetPlayerState<APPPlayerState>();
	checkf(playerState, TEXT("APPGameMode::AddPoint playerState is null"));

	playerState->AddPoint();
}

void APPGameMode::OnGameStarted()
{
	auto gameState = GetGameState<APPGameStateBase>();
	checkf(gameState, TEXT("APPGameMode::OnGameStarted gameState is null"));

	GetWorldTimerManager().SetTimer(StartGameDelayTimer, gameState, &APPGameStateBase::OnGameStarted, 1.0f, false);
}

void APPGameMode::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	GetWorldTimerManager().ClearTimer(StartGameDelayTimer);

	Super::EndPlay(endPlayReason);
}