// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


class AMirowinShooterGameMode;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MIROWIN_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URespawnComponent();

	void StartRespawn(int32 RespawnTime);
	void Respawn();

protected:
	virtual void BeginPlay() override;
	
private:
	FTimerHandle RespawnTimerHandle;

	UPROPERTY()
	AMirowinShooterGameMode* GameMode;
};
