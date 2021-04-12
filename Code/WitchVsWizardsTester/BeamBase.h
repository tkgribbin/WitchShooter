// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamBase.generated.h"

UCLASS()
class WITCHVSWIZARDSTESTER_API ABeamBase : public AActor
{
	GENERATED_BODY()
	
private:
	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* BeamParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* BeamTarget;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float Lifespan = 3.f;

public:
	// Sets default values for this actor's properties
	ABeamBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
