// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"

#include "BrainComponent.h"
#include "AI/MSAIController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	SpringArmComponent->SetRelativeLocation(FVector(10.f, 0.f, 70.f));
	SpringArmComponent->TargetArmLength = 250;
	SpringArmComponent->SocketOffset.Z = 20.0f;
	SpringArmComponent->SocketOffset.Y = 30.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	FirstPersonCameraComponent->DestroyComponent();
	Mesh1P->DestroyComponent();

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMSAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = {0.f, 250.f, 0.f};
	}
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<AAIController>(Controller);
	if(AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
