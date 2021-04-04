// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponProjectile.generated.h"

class AProjectileBase;

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AWeaponProjectile : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeaponProjectile();
	virtual void PullTrigger() override;

	FRotator GetShotRotation();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;

};
