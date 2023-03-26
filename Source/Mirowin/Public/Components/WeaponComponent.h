// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseWeapon.h"
#include "WeaponComponent.generated.h"

struct FAmmoData;
class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MIROWIN_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void StartFire();
	void StopFire();
	void Reload();

	FAmmoData GetAmmoData() const {return CurrentWeapon->GetAmmoData();}
	
	bool TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 AmmoAmount);
	bool NeedAmmo(TSubclassOf<ABaseWeapon> WeaponType);

	bool IsReloading() const {return CurrentWeapon->IsReloading();}
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> WeaponClass;

private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	TArray<ABaseWeapon*> Weapons;
	
	void SpawnWeapon();
};
