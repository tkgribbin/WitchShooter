// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class WITCHVSWIZARDSTESTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	virtual void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float Damage = 10;

	AController* GetOwnerController() const;
	
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* Flash;

	UPROPERTY(EditAnywhere)
		USoundBase* WeaponSound;

	


	


	
	

};