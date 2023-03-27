// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MirowinShooterHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AMirowinShooterHUD::AMirowinShooterHUD()
{
}

void AMirowinShooterHUD::DrawHUD()
{
	Super::DrawHUD();


	DrawCrosshair();

	// Draw very simple crosshair
	
	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	
	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + CrosshairTex->GetSizeY()/2.f));
	
	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AMirowinShooterHUD::DrawCrosshair()
{
	// const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	int32 SizeX= Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
}
