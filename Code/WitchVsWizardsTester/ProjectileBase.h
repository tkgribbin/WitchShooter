// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"


class UProjectileMovementComponent;

UCLASS()
class WITCHVSWIZARDSTESTER_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* ParticleTrail;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float MovementSpeed = 1300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float Lifespan = 3.f;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;
	UPROPERTY()
		float Damage;

	//Functions
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Sets default values for this actor's properties
	AProjectileBase();



	void SetDamage(float NewDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
