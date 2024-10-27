// Fill out your copyright notice in the Description page of Project Settings.

#include "PPPlayerPawn.h"

APPPlayerPawn::APPPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APPPlayerPawn::Move(float direction)
{
	MoveInternal(direction);
	MoveServer(direction);
}

void APPPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APPPlayerPawn::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	FString inputCompName = playerInputComponent != nullptr ? "NULL" : playerInputComponent->GetName();

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent %s"), *inputCompName);

	if (playerInputComponent != nullptr)
	{
		playerInputComponent->BindAxis("Move", this, &APPPlayerPawn::Move);
	}
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