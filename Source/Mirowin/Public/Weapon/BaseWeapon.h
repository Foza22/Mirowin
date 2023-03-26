// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ABaseCharacter;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoInClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AmmoInBackpack;
};

UCLASS()
class MIROWIN_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;

	void StartReload();

	bool TryToAddAmmo(float Amount);
	bool IsReloading() const { return GetWorldTimerManager().IsTimerActive(ReloadTimerHandle); }

	void AssignController(AActor* Character);

	FAmmoData GetAmmoData() const { return CurrentAmmo; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DecreaseAmmo();
	bool IsClipEmpty() const;
	void ChangeClip();
	void LogAmmo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	// Location on gun mesh where projectiles should spawn.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	// Gun muzzle's offset from the characters location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	// Sound to play each time we fire 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	// Sound to play each time we fire 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* NoAmmoSound;

	// Sound to play each time we fire 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	float ShootDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	FAmmoData MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	FAmmoData SpawnAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponBalance)
	float ReloadTime = 1.5f;
	
	UPROPERTY()
	ACharacter* Player;

	UPROPERTY()
	AController* Controller;

	virtual void MakeShot();
	void MakeDamage(const FHitResult& Hit);

	FAmmoData CurrentAmmo;

	// Assisting variable
	bool bCanFire = true;

	// Function to start reloading
	bool CanReload() const;

	FTimerHandle ReloadTimerHandle;
};
