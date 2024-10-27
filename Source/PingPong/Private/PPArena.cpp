// Fill out your copyright notice in the Description page of Project Settings.

#include "PPArena.h"
#include "PPBall.h"
#include "PPPlayerPawn.h"
#include "PPGameMode.h"
#include "PPGameStateBase.h"
#include "PPPlayerState.h"

#include "Engine/TargetPoint.h"
#include "Engine/TriggerBox.h"

APPArena::APPArena() :
	PlayerAmount(0)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	
	bNetLoadOnClient = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = true;
}

void APPArena::StartNewGame()
{
	Ball->SetActorLocation(BallSpawnPoint->GetActorLocation());
	Ball->Launch();
}

void APPArena::AddPlayer(APlayerController* newPlayer)
{
	const auto freeDataSlot = PlayerData.FindByPredicate([](const FPlayerData& data)
		{
			return data.Pawn->IsPawnControlled() == false;
		});
	
	if (freeDataSlot == nullptr)
		return;
	
	newPlayer->Possess(freeDataSlot->Pawn);
	++PlayerAmount;
	
	if (PlayerAmount == APPGameStateBase::PLAYER_AMOUNT)
	{
		StartNewGame();

		auto gameMode = GetWorld()->GetAuthGameMode<APPGameMode>();
		gameMode->OnGameStarted();
	}
}

void APPArena::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() == false)
		return;

	auto gameMode = GetWorld()->GetAuthGameMode<APPGameMode>();
	checkf(gameMode, TEXT("APPArena::BeginPlay gameMode is null"));

	gameMode->SetArena(this);

	if (PlayerData.Num() < APPGameStateBase::PLAYER_AMOUNT)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to setup arena"));
		return;
	}

	Setup();
}

void APPArena::Setup()
{
	SpawnBall();
	SpawnPawns();
	SetupTriggers();
}

void APPArena::SpawnBall()
{
	if (BallType)
	{
		Ball = GetWorld()->SpawnActor<APPBall>(BallType, BallSpawnPoint->GetActorLocation(), FRotator::ZeroRotator);
	}
}

void APPArena::SpawnPawns()
{
	for (int32 i = 0; i < APPGameStateBase::PLAYER_AMOUNT; i++)
	{
		auto& playerData = PlayerData[i];
		playerData.Pawn = GetWorld()->SpawnActor<APawn>(PlayerPawnType, playerData.SpawnPoint->GetActorLocation(), playerData.SpawnPoint->GetActorRotation());
	}
}

void APPArena::SetupTriggers()
{
	for (int32 i = 0; i < APPGameStateBase::PLAYER_AMOUNT; i++)
	{
		const auto& playerData = PlayerData[i];
		playerData.GoalTrigger->OnActorBeginOverlap.AddDynamic(this, &APPArena::OnGoalScored);
	}
}

void APPArena::OnGoalScored(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor->IsA<APPBall>() == false)
		return;

	auto data = PlayerData.FindByPredicate([=](const FPlayerData& data)
		{
			return data.GoalTrigger != overlappedActor;
		});

	if (data == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("data == nullptr"));
		return;
	}

	auto playerState = data->Pawn->GetPlayerState<APPPlayerState>();
	checkf(playerState, TEXT("APPArena::OnGoalScored playerState is null"));

	playerState->AddPoint();
	StartNewGame();
}
