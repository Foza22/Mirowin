// Fill out your copyright notice in the Description page of Project Settings.


#include "MirowinShooterGameMode.h"

#include "BaseCharacter.h"
#include "MirowinShooterHUD.h"

AMirowinShooterGameMode::AMirowinShooterGameMode() : Super()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();

	// use our custom HUD class
	HUDClass = AMirowinShooterHUD::StaticClass();
}
