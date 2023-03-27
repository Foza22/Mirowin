// Fill out your copyright notice in the Description page of Project Settings.


#include "MirowinShooterGameMode.h"

#include "AIController.h"
#include "BaseCharacter.h"
#include "MirowinShooterHUD.h"
#include "MSPlayerController.h"
#include "Components/RespawnComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

AMirowinShooterGameMode::AMirowinShooterGameMode() : Super()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();

	PlayerControllerClass = AMSPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = AMirowinShooterHUD::StaticClass();
}

void AMirowinShooterGameMode::StartPlay()
{
	Super::StartPlay();

	GetPlayerStarts();
	SpawnBots();
}

UClass* AMirowinShooterGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMirowinShooterGameMode::GetPlayerStarts()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);
	for (auto Actor : OutActors)
	{
		PlayerStarts.Emplace(Actor);
	}
}

AActor* AMirowinShooterGameMode::FindSuitablePlayerStart(AController* Controller)
{
	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), Characters);
	if(!Characters.Num()) return PlayerStarts[0];

	for(const auto PlayerStart : PlayerStarts)
	{
		UE_LOG(LogTemp, Display, TEXT("OUTER SCOPE"));
		for(const auto Character : Characters)
		{
			UE_LOG(LogTemp, Display, TEXT("INNER SCOPE"));
			const auto Distance = (Character->GetActorLocation() - PlayerStart->GetActorLocation()).Size();
			if(Distance < RespawnMinimalRadius)
			{
				UE_LOG(LogTemp, Display, TEXT("BREAK"));

				break;
			}
		}
		
		return PlayerStart;
	}

	return nullptr;
}

void AMirowinShooterGameMode::SpawnBots()
{
	UE_LOG(LogTemp, Display, TEXT("Spawn bots"));
	for (int32 i = 0; i < BotsNum; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		const auto PlayerStart = FindSuitablePlayerStart(AIController);
		RestartPlayerAtPlayerStart(AIController, PlayerStart);
	}
}


void AMirowinShooterGameMode::Killed(AController* KillerController, AController* VictimController)
{
	RespawnComponent = Cast<URespawnComponent>(VictimController->GetComponentByClass(URespawnComponent::StaticClass()));
	if (!RespawnComponent) return;

	RespawnComponent->StartRespawn(RespawnTime);
}

void AMirowinShooterGameMode::RequestRespawn(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
		Controller->UnPossess();
	}

	const auto PlayerStart = FindSuitablePlayerStart(Controller);
	RestartPlayerAtPlayerStart(Controller, PlayerStart);
}
