// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponBeam.generated.h"

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AWeaponBeam : public AWeapon
{
	GENERATED_BODY()

public:
	AWeaponBeam();
	virtual void PullTrigger() override;

private:

	bool WeaponTrace(FHitResult& Hit, FVector& ShotDirection);

	UPROPERTY(EditAnywhere)
		UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
		float MaxRange = 1000;

	//Handles shot delay
	FTimerHandle FlashTimerHandle;

	UPROPERTY(EditAnywhere)
		float FlashTime = 0.5f;

	bool bFlashVisible;

	void ResetFlash();

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* BeamParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* BeamTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* BeamSource;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float Lifespan = 3.f;
};