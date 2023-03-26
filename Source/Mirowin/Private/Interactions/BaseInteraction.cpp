// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/BaseInteraction.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseInteraction::ABaseInteraction()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractionArea = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionArea"));
	InteractionArea->InitSphereRadius(InteractionAreaRadius);
	InteractionArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionArea->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(InteractionArea);

	InteractMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractionMesh"));
	InteractMesh->SetupAttachment(InteractionArea);
}

// Called when the game starts or when spawned
void ABaseInteraction::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseInteraction::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;

	if (GivePickupTo(Pawn))
	{
		UE_LOG(LogTemp, Display, TEXT("PickupWasTaken"));
		InteractionWasUsed();
	}
}

void ABaseInteraction::InteractionWasUsed()
{
	InteractionArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);
	AddActorLocalOffset({0.f, 0.f, -HiddenOffset});
	UE_LOG(LogTemp, Display, TEXT("%f"), HiddenOffset);

	
	if (InteractSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, InteractSound, GetActorLocation());
	}

	OnInteract.Broadcast();
}

void ABaseInteraction::Respawn()
{
	GetRootComponent()->SetVisibility(true, true);
	InteractionArea->SetCollisionResponseToAllChannels(ECR_Overlap);
	AddActorLocalOffset({0.f, 0.f, HiddenOffset});

	if (SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, GetActorLocation());
	}
}

bool ABaseInteraction::GivePickupTo(APawn* PlayerPawn)
{
	// We can't pickup base object
	return false;
}
