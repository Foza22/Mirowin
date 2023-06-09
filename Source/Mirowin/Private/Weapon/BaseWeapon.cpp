// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BaseWeapon.h"

#include "BaseCharacter.h"
#include "DrawDebugHelpers.h"
#include "RespawnComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetOnlyOwnerSee(false); // otherwise won't be visible in the multiplayer
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(WeaponMesh);

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
	SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = SpawnAmmo;
}

void ABaseWeapon::StartFire()
{
}

void ABaseWeapon::StopFire()
{
}

void ABaseWeapon::MakeShot()
{
}

void ABaseWeapon::DecreaseAmmo()
{
	--CurrentAmmo.AmmoInClip;

	if (IsClipEmpty())
	{
		if(NoAmmoSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, NoAmmoSound, GetActorLocation());
		}

		if(!IsAmmoEmpty())
		StartReload();
	}
}

bool ABaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.AmmoInClip == 0;
}

bool ABaseWeapon::IsAmmoEmpty() const
{
	return IsClipEmpty() && CurrentAmmo.AmmoInBackpack == 0;
}

bool ABaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.AmmoInBackpack == MaxAmmo.AmmoInBackpack;
}

void ABaseWeapon::StartReload()
{
	if(!CanReload()) return;

	bCanFire = false;
	StopFire();

	if(ReloadSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
	}

	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ABaseWeapon::ChangeClip, ReloadTime, false);
}

bool ABaseWeapon::CanReload() const
{
	return CurrentAmmo.AmmoInClip < MaxAmmo.AmmoInClip && CurrentAmmo.AmmoInBackpack > 0;
}

void ABaseWeapon::ChangeClip()
{
	const auto AmmoNeeded = MaxAmmo.AmmoInClip - CurrentAmmo.AmmoInClip;
	if (AmmoNeeded == 0) return;

	if (AmmoNeeded > CurrentAmmo.AmmoInBackpack)
	{
		CurrentAmmo.AmmoInClip += CurrentAmmo.AmmoInBackpack;
		CurrentAmmo.AmmoInBackpack = 0;
	}
	else
	{
		CurrentAmmo.AmmoInClip += AmmoNeeded;
		CurrentAmmo.AmmoInBackpack -= AmmoNeeded;
	}

	bCanFire = true;
}

bool ABaseWeapon::TryToAddAmmo(float Amount)
{
	if(IsAmmoFull()) return false;

	const auto AmmoCanBeAdded = MaxAmmo.AmmoInBackpack - CurrentAmmo.AmmoInBackpack;

	Amount = Amount > AmmoCanBeAdded ? AmmoCanBeAdded : Amount;

	CurrentAmmo.AmmoInBackpack += Amount;

	if(CurrentAmmo.AmmoInClip == 0)
	{
		StartReload();
	}

	return true;
}

void ABaseWeapon::MakeDamage(const FHitResult& Hit)
{
	const auto DamagedActor = Hit.GetActor();
	if (!DamagedActor) return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), Controller, Player);
}

void ABaseWeapon::AssignController()
{
	Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	UE_LOG(LogTemp, Display, TEXT("Trying to get controller"));
	
	Controller = Player->GetController();
	
	if(Controller)
	{
		UE_LOG(LogTemp, Display, TEXT("Assigned %s"), *Controller->GetName());
	}
}
