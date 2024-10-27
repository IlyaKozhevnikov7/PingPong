// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PPGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStarted);

UCLASS()
class PINGPONG_API APPGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	constexpr static uint32 PLAYER_AMOUNT = 2;

	UPROPERTY(BlueprintAssignable)
	FOnGameStarted OnGameStartedEvent;
	
public:

	UFUNCTION(NetMulticast, Reliable)
	void OnGameStarted();
};
