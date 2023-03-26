// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MIROWIN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	float GetHealth() const { return Health; }
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0.f; }

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	                     AActor* DamageCauser);

	FOnDeath OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly, blueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
};
