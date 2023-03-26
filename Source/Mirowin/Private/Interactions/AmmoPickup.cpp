
// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactions/AmmoPickup.h"

#include "Components/WeaponComponent.h"

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto WeaponComponent = Cast<UWeaponComponent>(PlayerPawn->GetComponentByClass(UWeaponComponent::StaticClass()));
	if(!WeaponComponent) return false;

	UE_LOG(LogTemp, Display, TEXT("HERE WE HAVE COMP"));

	return WeaponComponent->TryToAddAmmo(WeaponType, AmmoAmount);
}
