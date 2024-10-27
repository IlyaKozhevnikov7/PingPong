// Fill out your copyright notice in the Description page of Project Settings.

#include "PPPlayerPawn.h"

void APPPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	bReplicates = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = true;

	SetReplicateMovement(true);
}

void APPPlayerPawn::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	playerInputComponent->BindAxis("Move", this, &APPPlayerPawn::Move);
}

void APPPlayerPawn::Move(float direction)
{
	MoveInternal(direction);
	MoveServer(direction);
}

void APPPlayerPawn::MoveServer_Implementation(float direction)
{
	MoveInternal(direction);
}

bool APPPlayerPawn::MoveServer_Validate(float direction)
{
	return direction >= -1.f && direction <= 1.f;
}

void APPPlayerPawn::MoveInternal(float direction)
{
	const auto offset = direction * GetActorRightVector() * MoveSpeed;
	SetActorLocation(GetActorLocation() + offset, true);
}