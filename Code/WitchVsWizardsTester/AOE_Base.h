// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AOE_Base.generated.h"

UCLASS()
class WITCHVSWIZARDSTESTER_API AAOE_Base : public AActor
{
	GENERATED_BODY()
	
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* EffectMesh;
	UPROPERTY(EditAnywhere, Category = "Components")
		UParticleSystem* EffectParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UBoxComponent* CollisionBox = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USphereComponent* CollisionSphere = nullptr;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float Damage;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		bool bUseBox;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float Lifespan = 3.f;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* HitSound;
	
	

	//Functions
	
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void DealDamage(AActor* OtherActor, float DamageAmount, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> ThisDamageType);



	FTimerHandle OverlapTimerHandle;
	FTimerDelegate OverlapTimerDelegate;

	UPROPERTY(EditAnywhere)
		float DamageDelay = 1.f;
	
	void TimedFunction();

	bool bIsOverlap = false; //bFlashVisible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		bool bContinuous;

public:
	// Sets default values for this actor's properties
	AAOE_Base();

	void SetDamage(float NewDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
};