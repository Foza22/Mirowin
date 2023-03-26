// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MSPlayerController.h"
#include "Components/RespawnComponent.h"

AMSPlayerController::AMSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));
}
