// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponProjectile.generated.h"

class AProjectileBase;

UCLASS()
class WITCHVSWIZARDSTESTER_API AWeaponProjectile : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeaponProjectile();
	virtual void PullTrigger() override;

	FRotator GetShotRotation(FVector HitLocation);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;

	bool WeaponTrace(FHitResult& Hit, FVector& ShotDirection);

	void SpawnProjectile(FVector Location, FRotator Rotation);

	FVector GetSpawnLocation();

	FRotator GetSpawnRotation();

	UPROPERTY(EditAnywhere)
		float MaxRange = 10000;
};
