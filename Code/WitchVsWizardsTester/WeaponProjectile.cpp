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

	SpawnProjectile(GetSpawnLocation(), GetSpawnRotation());
}

FVector AWeaponProjectile::GetSpawnLocation()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

FRotator AWeaponProjectile::GetSpawnRotation()
{
	FRotator SpawnRotation;
	FVector HitLocation;
	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = WeaponTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		HitLocation = Hit.Location;
		SpawnRotation = GetShotRotation(HitLocation);
	}
	else
	{
		FVector Location;
		FRotator Rotation;

		AController* OwnerController = GetOwnerController();
		if (!OwnerController) return SpawnRotation;

		OwnerController->GetPlayerViewPoint(Location, Rotation);
		return Rotation;
	}

	return SpawnRotation;
}

FRotator AWeaponProjectile::GetShotRotation(FVector HitLocation)
{
	FVector Location;
	FRotator Rotation;
	
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return Rotation;
	
	FVector Result;
	Result = HitLocation - (ProjectileSpawnPoint->GetComponentLocation());
	Rotation = Result.GetSafeNormal().Rotation();

	return Rotation;
}

bool AWeaponProjectile::WeaponTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

void AWeaponProjectile::SpawnProjectile(FVector Location, FRotator Rotation)
{
	if (ProjectileClass)
	{
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
		TempProjectile->SetOwner(this);
		TempProjectile->SetDamage(Damage);
	}
}


