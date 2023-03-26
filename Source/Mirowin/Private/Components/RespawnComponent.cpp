// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RespawnComponent.h"

#include "HealthComponent.h"
#include "MirowinShooterGameMode.h"

// Sets default values for this component's properties
URespawnComponent::URespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void URespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMirowinShooterGameMode>(GetWorld()->GetAuthGameMode());
}

void URespawnComponent::StartRespawn(int32 RespawnTime)
{
	if(!GameMode) return;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &URespawnComponent::Respawn,
	                                       RespawnTime, false);
}

void URespawnComponent::Respawn()
{
	UE_LOG(LogTemp, Display, TEXT("RESPAWN"));
	GameMode->RequestRespawn(Cast<AController>(GetOwner()));
}
