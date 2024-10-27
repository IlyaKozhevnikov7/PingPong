// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/PPScoreWidget.h"
#include "PPGameStateBase.h"
#include "PPPlayerState.h"
#include "Components/TextBlock.h"

void UPPScoreWidget::NativeOnInitialized()
{
	auto gameState = GetWorld()->GetGameState<APPGameStateBase>();
	gameState->OnGameStartedEvent.AddDynamic(this, &UPPScoreWidget::OnGameStarted);

	Super::NativeOnInitialized();
}

void UPPScoreWidget::OnGameStarted()
{
	auto gameState = GetWorld()->GetGameState<APPGameStateBase>();

	for (int32 i = 0; i < APPGameStateBase::PLAYER_AMOUNT; i++)
	{
		const auto playerState = Cast<APPPlayerState>(gameState->PlayerArray[i]);
		check(playerState);

		PlayerScoreTexts.Add(playerState, GetScoreText(i));
	}

	for (auto& pair : PlayerScoreTexts)
	{
		pair.Key->OnScoreChanged.AddDynamic(this, &UPPScoreWidget::OnScoreChanged);
	}
}

void UPPScoreWidget::OnScoreChanged(APPPlayerState* playerState)
{
	check(PlayerScoreTexts.Contains(playerState));
	PlayerScoreTexts[playerState]->SetText(FText::AsNumber(playerState->GetScore()));
}
