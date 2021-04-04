// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponProjectile.h"
#include "ProjectileBase.h"


AWeaponProjectile::AWeaponProjectile()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(Root);
}

void AWeaponProjectile::PullTrigger()
{
	Super::PullTrigger();

	//Spawn Projectile at flash position
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = GetShotRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}


FRotator AWeaponProjectile::GetShotRotation()
{
	FVector Location;
	FRotator Rotation;
	
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return Rotation;
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	return Rotation;
}
