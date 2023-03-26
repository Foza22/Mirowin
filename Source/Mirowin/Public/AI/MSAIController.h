// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MSAIController.generated.h"


class UMSAIPerceptionComponent;
class URespawnComponent;

UCLASS()
class MIROWIN_API AMSAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMSAIController();

	URespawnComponent* GetRespawnComponent() const {return RespawnComponent;}

protected:
	UPROPERTY(VisibleAnywhere)
	URespawnComponent* RespawnComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMSAIPerceptionComponent* MSPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
	
};
