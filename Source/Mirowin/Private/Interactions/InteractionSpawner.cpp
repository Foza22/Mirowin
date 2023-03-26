// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/InteractionSpawner.h"
#include "Interactions/BaseInteraction.h"

// Sets default values
AInteractionSpawner::AInteractionSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractionSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!SpawnObject) return;

	if (bSpawnOnBegin)
		Spawn();
	else
		GetWorldTimerManager().SetTimer(SpawnDelayTimerHandle, this, &AInteractionSpawner::Spawn, SpawnDelay, false);
}

void AInteractionSpawner::Spawn()
{
	InteractionObject = GetWorld()->SpawnActor<ABaseInteraction>(SpawnObject);
	if(!InteractionObject) return;
	
	InteractionObject->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if(bRespawnItem)
	{
		InteractionObject->OnInteract.AddDynamic(this, &AInteractionSpawner::StartRespawn);
	}
}

void AInteractionSpawner::StartRespawn()
{
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, InteractionObject, &ABaseInteraction::Respawn, RespawnTime, false);
}
