// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MSAIPerceptionComponent.h"

#include "HealthComponent.h"
#include "MSAIController.h"
#include "Perception/AISense_Sight.h"

AActor* UMSAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> VisibleActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), VisibleActors);
	if(VisibleActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AMSAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for(auto Actor : VisibleActors)
	{
		const auto HealthComponent = Cast<UHealthComponent>(Actor->GetComponentByClass(UHealthComponent::StaticClass()));
		if(HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if(CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = Actor;
			}
		}
	}

	return BestPawn;
}
