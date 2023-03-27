// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MirowinShooterHUD.generated.h"

/**
 * 
 */
UCLASS()
class MIROWIN_API AMirowinShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMirowinShooterHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:
	void DrawCrosshair();
	
	/** Crosshair asset pointer */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture2D* CrosshairTex;
};
