// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "AmmoAmountDecorator.generated.h"

class ABaseWeapon;
UCLASS()
class MIROWIN_API UAmmoAmountDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UAmmoAmountDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> WeaponType;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
