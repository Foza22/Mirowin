// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactions/BaseInteraction.h"
#include "AmmoPickup.generated.h"

class ABaseWeapon;
UCLASS()
class MIROWIN_API AAmmoPickup : public ABaseInteraction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1.0"));
	int32 AmmoAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (ClampMin = "1.0", ClampMax = "10.0"));
	TSubclassOf<ABaseWeapon> WeaponType;

	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
