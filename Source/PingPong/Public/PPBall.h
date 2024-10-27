// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBall.generated.h"

class USphereComponent;

UCLASS()
class PINGPONG_API APPBall : public AActor
{
	GENERATED_BODY()
	
private:


	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* Collision = nullptr;

public:	

	APPBall();

	void Launch();

private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
