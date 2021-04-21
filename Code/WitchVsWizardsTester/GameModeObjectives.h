// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WitchVsWizardsTesterGameModeBase.h"
#include "GameModeObjectives.generated.h"


/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AGameModeObjectives : public AWitchVsWizardsTesterGameModeBase
{
	GENERATED_BODY()
	
private:
	

public:
	UPROPERTY(EditAnywhere)
		int32 CurrentObjective = 1;
	
	UFUNCTION()
		void SetObjective(int NewObjective);
	UFUNCTION()
		int32 GetCurrentObjective();
};
