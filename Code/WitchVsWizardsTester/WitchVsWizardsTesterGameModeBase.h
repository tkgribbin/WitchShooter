// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WitchVsWizardsTesterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API AWitchVsWizardsTesterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled);

};
