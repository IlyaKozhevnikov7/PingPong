// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PPPlayerPawn.generated.h"

class UInputComponent;

UCLASS()
class PINGPONG_API APPPlayerPawn : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 20.f;

	FName MoveInputName = "Move";

private:

	void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

	void Move(float direction);

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveServer(float direction);

	void MoveInternal(float direction);
};
