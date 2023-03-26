// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionSpawner.generated.h"

class ABaseInteraction;
UCLASS()
class MIROWIN_API AInteractionSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InteractionSettings)
	TSubclassOf<ABaseInteraction> SpawnObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InteractionSettings)
	bool bSpawnOnBegin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InteractionSettings, meta = (EditCondition = "!bSpawnOnBegin"))
	float SpawnDelay = 3.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InteractionSettings)
	bool bRespawnItem = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=InteractionSettings,  meta = (EditCondition = "bRespawnItem"))
	float RespawnTime = 5.f;

private:
	void Spawn();

	UFUNCTION()
	void StartRespawn();

	UPROPERTY()
	ABaseInteraction* InteractionObject;
	
	FTimerHandle RespawnTimerHandle;
	FTimerHandle SpawnDelayTimerHandle;
};
