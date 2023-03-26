// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MSAIController.h"
#include "Components/RespawnComponent.h"
#include "AICharacter.h"
#include "BaseCharacter.h"
#include "MSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMSAIController::AMSAIController()
{
	MSPerceptionComponent = CreateDefaultSubobject<UMSAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*MSPerceptionComponent);
	
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>(TEXT("RespawnComponent"));
}

void AMSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* AMSAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

void AMSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAICharacter>(InPawn);
	if(AICharacter)
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}


