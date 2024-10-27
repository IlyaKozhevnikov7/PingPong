// Fill out your copyright notice in the Description page of Project Settings.

#include "PPBall.h"
#include <Components/SphereComponent.h>

APPBall::APPBall()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bReplicates = true;
	bAlwaysRelevant = true;
	bNetLoadOnClient = true;
	SetReplicateMovement(true);

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetSimulatePhysics(false);
	SetRootComponent(Collision);
}

void APPBall::Launch()
{
	check(HasAuthority());

	const int32 angleMultiplier = FMath::RandRange(0.0, 3.0);
	const double angle = 45 + 90 * angleMultiplier;

	SetActorRotation(FRotator(0, angle, 0));
	SetActorTickEnabled(true);
}

void APPBall::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Collision->OnComponentHit.AddDynamic(this, &APPBall::OnCollisionHit);
	}
}

void APPBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto location = GetActorLocation();
	DrawDebugLine(GetWorld(), location, location + GetActorForwardVector() * 500.f, FColor::Blue, false);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * MoveSpeed, true);
}

void APPBall::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DrawDebugLine(GetWorld(), Hit.Location, Hit.Location + Hit.Normal * 100.f, FColor::Red, false, 10.f);

	const auto forward = GetActorForwardVector();

	const auto project = FVector::DotProduct(Hit.Normal, -forward) * Hit.Normal;
	const auto reject = (project - (-forward)) * 2.f;
	const auto reflect = (reject - forward).GetSafeNormal();

	SetActorRotation(reflect.Rotation());
}
