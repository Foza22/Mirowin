// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FireService.h"

#include "AIController.h"
#include "WeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UFireService::UFireService()
{
	NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller)
	{ 
		const auto WeaponComponent = Cast<UWeaponComponent>(Controller->GetPawn()->GetComponentByClass(UWeaponComponent::StaticClass()));
		if(WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
