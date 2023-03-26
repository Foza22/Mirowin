// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

#include "AICharacter.h"
#include "BaseCharacter.h"
#include "Weapon/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Display, TEXT("Begin play"));
	
	Weapons.Empty();
	CurrentWeapon = nullptr;
	
	SpawnWeapon();
}


void UWeaponComponent::SpawnWeapon()
{
	UE_LOG(LogTemp, Display, TEXT("Spawn weapon"));

	const auto Character = Cast<ABaseCharacter>(GetOwner());
	if(!Character) return;
	
	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	USkeletalMeshComponent* Mesh = Character->GetCharacterMesh();
	
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	CurrentWeapon->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
							  TEXT("GripPoint"));

	CurrentWeapon->SetOwner(Character);
	CurrentWeapon->AssignController();

	UE_LOG(LogTemp, Display, TEXT("Spawned successful"));

	Weapons.Emplace(CurrentWeapon);
}

void UWeaponComponent::StartFire()
{
	UE_LOG(LogTemp, Display, TEXT("Try to fire"));
	if(!CurrentWeapon) return;
	UE_LOG(LogTemp, Display, TEXT("Succeed to fire"));

	CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

void UWeaponComponent::Reload()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StartReload();
}

bool UWeaponComponent::TryToAddAmmo(TSubclassOf<ABaseWeapon> WeaponType, int32 AmmoAmount)
{
	for(auto Weapon : Weapons)
	{
		if(Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(AmmoAmount);
		}
	}
	
	return false;
}

bool UWeaponComponent::NeedAmmo(TSubclassOf<ABaseWeapon> WeaponType)
{
	for(auto Weapon : Weapons)
	{
		if(Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}

	return false;
}