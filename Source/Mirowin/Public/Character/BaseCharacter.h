// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AMirowinShooterGameMode;
class URespawnComponent;
class UHealthComponent;
class ABaseWeapon;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UWeaponComponent;

UCLASS(config=Game)
class ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjInit);

	UHealthComponent* GetHealthComponent() const {return HealthComponent;}
	UWeaponComponent* GetWeaponComponent() const {return WeaponComponent;}

	virtual USkeletalMeshComponent* GetCharacterMesh() const { return Mesh1P; }

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath();

	void MoveForward(float Val);

	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* WeaponComponent;

	UPROPERTY()
	AMirowinShooterGameMode* GameMode;
};
