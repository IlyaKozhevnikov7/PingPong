// Fill out your copyright notice in the Description page of Project Settings.

#include "PPPlayerState.h"

void APPPlayerState::AddPoint()
{
	check(HasAuthority());
	SetScore(GetScore() + 1);
}

void APPPlayerState::OnRep_Score()
{
	OnScoreChanged.Broadcast(this);
}
