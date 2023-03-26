// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"


class UWeaponComponent;
class ABaseCharacter;
UCLASS()
class MIROWIN_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UI function for current ammo
	UFUNCTION(BlueprintCallable, Category = Weapon)
		int32 GetAmmoInClip() const;
	
	// UI function for ammo in total
	UFUNCTION(BlueprintCallable, Category = Weapon)
		int32 GetAmmoInBackPack() const;

	// Function for drawing UI reloading
	UFUNCTION(BlueprintCallable, Category = Weapon)
		bool IsReloading() const;

protected:
	virtual void NativeOnInitialized() override;

	// UPROPERTY()
	// ABaseCharacter* Player;
	//
	// UPROPERTY()
	// UWeaponComponent* WeaponComponent;
};
