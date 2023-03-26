// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AmmoWidget.h"
#include "Components/WeaponComponent.h"
#include "BaseCharacter.h"

void UAmmoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

int32 UAmmoWidget::GetAmmoInClip() const
{
	const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	if(!Player) return 0;
	
	const auto WeaponComponent = Player->GetWeaponComponent();
	
	if(!WeaponComponent) return 0;

	return WeaponComponent->GetAmmoData().AmmoInClip;
}

int32 UAmmoWidget::GetAmmoInBackPack() const
{
	const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	if(!Player) return 0;
	
	const auto WeaponComponent = Player->GetWeaponComponent();
	
	if(!WeaponComponent) return 0;

	return WeaponComponent->GetAmmoData().AmmoInBackpack;
}

bool UAmmoWidget::IsReloading() const
{
	const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	if(!Player) return false;
	
	const auto WeaponComponent = Player->GetWeaponComponent();
	
	if(!WeaponComponent) return false;

	return WeaponComponent->IsReloading();
}


