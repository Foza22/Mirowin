// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AmmoWidget.h"
#include "Components/WeaponComponent.h"
#include "BaseCharacter.h"

void UAmmoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	if(!Player) return;
	
	WeaponComponent = Player->GetWeaponComponent();
}

int32 UAmmoWidget::GetAmmoInClip() const
{
	if(!Player || !WeaponComponent) return 0;

	return WeaponComponent->GetAmmoData().AmmoInClip;
}

int32 UAmmoWidget::GetAmmoInBackPack() const
{
	if(!Player || !WeaponComponent) return 0;

	return WeaponComponent->GetAmmoData().AmmoInBackpack;
}

bool UAmmoWidget::IsReloading() const
{
	if(!Player || !WeaponComponent) return 0;

	return WeaponComponent->IsReloading();
}


