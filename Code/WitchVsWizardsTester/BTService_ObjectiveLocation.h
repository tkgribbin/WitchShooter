// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ObjectiveLocation.generated.h"

/**
 * 
 */
UCLASS()
class WITCHVSWIZARDSTESTER_API UBTService_ObjectiveLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_ObjectiveLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};