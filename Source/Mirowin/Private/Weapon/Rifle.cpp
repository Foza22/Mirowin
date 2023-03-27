// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Rifle.h"

#include "DrawDebugHelpers.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"

void ARifle::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60.f / ShootingRate;
}


void ARifle::StartFire()
{
	if (!Controller || !Player)	return;

	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifle::MakeShot, TimeBetweenShots, true);
}

void ARifle::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ARifle::MakeShot()
{
	if (!bCanFire) return;

	if (IsClipEmpty())
	{
		if (NoAmmoSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, NoAmmoSound, GetActorLocation());
		}

		StopFire();
		return;
	}

	FVector ViewLocation;
	FRotator ViewRotation;

	if (Player->IsPlayerControlled())
	{
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = WeaponMesh->GetSocketLocation("Muzzle");
		ViewRotation = WeaponMesh->GetSocketRotation("Muzzle");
	}

	const auto TraceStart = ViewLocation;
	const auto TraceEnd = TraceStart + ViewRotation.Vector() * ShootDistance;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Player);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5);

	if (Hit.bBlockingHit)
	{
		MakeDamage(Hit);
		//DrawDebugSphere(GetWorld(), Hit.Location, 25, 12, FColor::Blue, false, 5);
	}

	DecreaseAmmo();
	PlaySound();
}

void ARifle::PlaySound()
{
	if (CurrentAmmo.AmmoInClip < LowAmmoLevel)
	{
		if (LowAmmoSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LowAmmoSound, GetActorLocation());
			return;
		}
	}

	// try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}
