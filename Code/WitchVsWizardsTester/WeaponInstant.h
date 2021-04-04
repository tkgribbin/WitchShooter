// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponInstant.generated.h"

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AWeaponInstant : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponInstant();
	virtual void PullTrigger() override;

private:
	
	bool WeaponTrace(FHitResult& Hit, FVector& ShotDirection);
	



	UPROPERTY(EditAnywhere)
		UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
		float MaxRange = 1000;
	
};
