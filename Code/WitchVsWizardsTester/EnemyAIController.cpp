// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharacterBase.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    AGameModeObjectives* const GameModeObjectives = GetWorld()->GetAuthGameMode<AGameModeObjectives>();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsInt(TEXT("ObjectiveNumber"),  GameModeObjectives->GetCurrentObjective());
    }
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool AEnemyAIController::IsDead() const
{
   ACharacterBase* ControlledCharacter = Cast<ACharacterBase>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }
    return true;
}