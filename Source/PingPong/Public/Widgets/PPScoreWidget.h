// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPScoreWidget.generated.h"

class UTextBlock;
class APPPlayerState;

UCLASS()
class PINGPONG_API UPPScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FirstPlayerScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SecondPlayerScoreText;

	TMap<APPPlayerState*, UTextBlock*> PlayerScoreTexts;

private:

	void NativeOnInitialized() override;

	UFUNCTION()
	void OnGameStarted();

	UFUNCTION()
	void OnScoreChanged(APPPlayerState* playerState);

	UTextBlock* GetScoreText(int32 index) const
	{
		return index == 0 ? FirstPlayerScoreText : SecondPlayerScoreText;
	}
};
