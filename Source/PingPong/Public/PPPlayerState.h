// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, APPPlayerState*, PlayerState);

UCLASS()
class PINGPONG_API APPPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
		
	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

public:

	void AddPoint();

private:

	void OnRep_Score() override;
};
