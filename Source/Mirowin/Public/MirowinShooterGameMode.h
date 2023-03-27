// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MirowinShooterGameMode.generated.h"

class URespawnComponent;
class ABaseCharacter;
class AAIController;
UCLASS()
class MIROWIN_API AMirowinShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMirowinShooterGameMode();

	void RequestRespawn(AController* Controller);

	void Killed(AController* KillerController, AController* VictimController);

	float GetRespawnTime() const { return RespawnTime; }

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY()
	TArray<AActor*> PlayerStarts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	int32 BotsNum = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	float RespawnTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Game)
	float RespawnMinimalRadius = 500.f;

private:
	void SpawnBots();
	void GetPlayerStarts();

	AActor* FindSuitablePlayerStart(AController* Controller);

	FTimerHandle RespawnTimerHandle;

	UPROPERTY()
	URespawnComponent* RespawnComponent;
};
