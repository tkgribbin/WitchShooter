// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponFromBody.generated.h"

class AProjectileBase;

UCLASS()
class WITCHVSWIZARDSTESTER_API AWeaponFromBody : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponFromBody();
	virtual void PullTrigger() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	AActor* OwnerActor;
	float Offset = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;
	
};
