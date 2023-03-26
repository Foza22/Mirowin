// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "GameFramework/Character.h"
#include "MirowinShooterGameMode.h"

UHealthComponent::UHealthComponent()
{
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	auto ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		UE_LOG(LogTemp, Display, TEXT("HERE IS THE OWNER"));
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}


void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                       AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f || IsDead()) return;

	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), Damage);
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}
