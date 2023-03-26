// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteraction.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS()
class MIROWIN_API ABaseInteraction : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABaseInteraction();

	FOnInteract OnInteract;

	void Respawn();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* InteractMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* InteractionArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* InteractSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=BaseInteraction)
	float HiddenOffset = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float InteractionAreaRadius = 100.f;

	void InteractionWasUsed();

	virtual bool GivePickupTo(APawn* PlayerPawn);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
