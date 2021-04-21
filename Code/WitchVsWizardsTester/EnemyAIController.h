// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "GameModeObjectives.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
};