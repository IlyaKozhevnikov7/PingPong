// Fill out your copyright notice in the Description page of Project Settings.

#include "PPGameStateBase.h"

void APPGameStateBase::OnGameStarted_Implementation()
{
	if (HasAuthority())
		return;

	OnGameStartedEvent.Broadcast();
}

