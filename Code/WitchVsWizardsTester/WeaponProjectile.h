// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponProjectile.generated.h"

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

private:
	//Is needed? Move to Weapon Base
	//AController* GetOwnerController() const;

};
