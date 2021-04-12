// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponFromBody.h"
#include "ProjectileBase.h"

AWeaponFromBody::AWeaponFromBody()
{

}

void AWeaponFromBody::BeginPlay()
{
	Super::BeginPlay();

}

void AWeaponFromBody::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("Pull Trigger"));
	
	//Get transform / Rotation of owner pawn
	if (!OwnerActor) 
	{ 
		OwnerActor = GetOwner();
		UE_LOG(LogTemp, Warning, TEXT("Set Owner")); 
	}

	if (!OwnerActor) { return; }
	
	FVector SpawnLocation = OwnerActor->GetActorLocation();
	FVector SpawnOffset = OwnerActor->GetActorForwardVector() * Offset;
	FRotator SpawnRotation = OwnerActor->GetActorRotation();
	
	//Spawn Wave (Hitbox) at transform, with rotation
	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation + SpawnOffset, SpawnRotation);
	TempProjectile->SetOwner(this);

	//Play Animation
	//Remove when complete
}

