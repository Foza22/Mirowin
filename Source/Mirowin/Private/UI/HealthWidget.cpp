// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthWidget.h"

#include "BaseCharacter.h"
#include "HealthComponent.h"

float UHealthWidget::GetHealthPercent() const
{
	const auto Pawn = GetOwningPlayerPawn();
	const auto Player = Cast<ABaseCharacter>(Pawn);
	if(!Player) return 0;

	const auto HealthComponent = Player->GetHealthComponent();
	if(!HealthComponent) return 0;

	return HealthComponent->GetHealth()/HealthComponent->GetMaxHealth();
}
