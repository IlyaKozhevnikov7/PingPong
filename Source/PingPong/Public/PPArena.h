// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPArena.generated.h"

class APPGameMode;
class APPBall;
class APPPlayerPawn;
class ATriggerBox;
class ATargetPoint;

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly)
	ATriggerBox* GoalTrigger;

	UPROPERTY(EditInstanceOnly)
	ATargetPoint* SpawnPoint;

	UPROPERTY()
	APawn* Pawn;
};

UCLASS()
class PINGPONG_API APPArena : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditInstanceOnly, Category = "PingPong")
	TArray<FPlayerData> PlayerData;

	UPROPERTY(EditInstanceOnly, Category = "PingPong")
	ATargetPoint* BallSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "PingPong")
	TSubclassOf<APPBall> BallType;

	UPROPERTY(EditDefaultsOnly, Category = "PingPong")
	TSubclassOf<APPPlayerPawn> PlayerPawnType;

	UPROPERTY()
	APPBall* Ball;

	uint32 PlayerAmount;

public:

	APPArena();

public:

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	}

	void StartNewGame();

	void AddPlayer(APlayerController* newPlayer);

private:

	virtual void BeginPlay() override;

	void Setup();

	void SpawnBall();

	void SpawnPawns();

	void SetupTriggers();

	UFUNCTION()
	void OnGoalScored(AActor* overlappedActor, AActor* otherActor);
};
