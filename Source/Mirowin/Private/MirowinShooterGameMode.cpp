// Fill out your copyright notice in the Description page of Project Settings.


#include "MirowinShooterGameMode.h"

#include "AIController.h"
#include "BaseCharacter.h"
#include "MirowinShooterHUD.h"
#include "MSPlayerController.h"
#include "Components/RespawnComponent.h"
#include "Kismet/GameplayStatics.h"

AMirowinShooterGameMode::AMirowinShooterGameMode() : Super()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AMirowinShooterHUD::StaticClass();
}

void AMirowinShooterGameMode::StartPlay()
{
	Super::StartPlay();
	
	SpawnBots();
}

UClass* AMirowinShooterGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMirowinShooterGameMode::SpawnBots()
{
	UE_LOG(LogTemp, Display, TEXT("Spawn bots"));
	for(int32 i = 0; i < BotsNum; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

void AMirowinShooterGameMode::Killed(AController* KillerController, AController* VictimController)
{
	RespawnComponent = Cast<URespawnComponent>(VictimController->GetComponentByClass(URespawnComponent::StaticClass()));
	if(!RespawnComponent) return;
	
	RespawnComponent->StartRespawn(RespawnTime);
}

void AMirowinShooterGameMode::RequestRespawn(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		UE_LOG(LogTemp, Display, TEXT("Controller is valid"));
		Controller->GetPawn()->Reset();
		Controller->UnPossess();
	}
	
	RestartPlayer(Controller);
}