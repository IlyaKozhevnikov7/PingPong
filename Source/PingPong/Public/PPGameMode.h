// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameMode.generated.h"

class APPArena;

UCLASS()
class PINGPONG_API APPGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	APPArena* Arena;

	FTimerHandle StartGameDelayTimer;

public:

	virtual void PostLogin(APlayerController* newPlayer);

	void SetArena(APPArena* arena);

	void AddPoint(APlayerController* controller);

	void OnGameStarted();

private:

	void EndPlay(const EEndPlayReason::Type endPlayReason) override;
};
