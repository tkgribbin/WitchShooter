// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapon_AOE.generated.h"

class AAOE_Base;
/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AWeapon_AOE : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeapon_AOE();
	virtual void PullTrigger() override;

	FRotator GetShotRotation(FVector HitLocation);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* AOE_SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AAOE_Base> AOE_Class;

	bool WeaponTrace(FHitResult& Hit, FVector& ShotDirection);

	void SpawnAOE(FVector Location, FRotator Rotation);

	//FVector GetSpawnLocation();

	//FRotator GetSpawnRotation();

	UPROPERTY(EditAnywhere)
		float MaxRange = 10000;
};