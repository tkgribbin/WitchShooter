// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeObjectives.h"

void AGameModeObjectives::SetObjective(int NewObjective)
{
	CurrentObjective = NewObjective;
}

int32 AGameModeObjectives::GetCurrentObjective()
{
	return CurrentObjective;
}
