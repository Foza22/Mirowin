// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "Rifle.generated.h"


UCLASS()
class MIROWIN_API ARifle : public ABaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	int32 ShootingRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	int32 LowAmmoLevel = 5;

	// Sound to play each time we fire 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* LowAmmoSound;

	virtual void BeginPlay() override;
	
private:

	void PlaySound();
	
	float TimeBetweenShots;

	FTimerHandle ShotTimerHandle;
};
