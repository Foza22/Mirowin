// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MSPlayerController.generated.h"

class URespawnComponent;

UCLASS()
class MIROWIN_API AMSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMSPlayerController();
	
	URespawnComponent* GetRespawnComponent() const {return RespawnComponent;}
	
protected:
	UPROPERTY(VisibleAnywhere)
	URespawnComponent* RespawnComponent;
};
