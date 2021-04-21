// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ObjectiveLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeObjectives.h"

UBTService_ObjectiveLocation::UBTService_ObjectiveLocation()
{
    NodeName = "Update Objective Location";
}
void UBTService_ObjectiveLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AGameModeObjectives* const GameModeObjectives = GetWorld()->GetAuthGameMode<AGameModeObjectives>();
    int32 ObjectiveNumber = GameModeObjectives->GetCurrentObjective();

    
    /*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());*/
}
