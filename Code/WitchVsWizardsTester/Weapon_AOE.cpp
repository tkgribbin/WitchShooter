// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_AOE.h"
#include "AOE_Base.h"

AWeapon_AOE::AWeapon_AOE()
{
	AOE_SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AOE Spawn Point"));
	AOE_SpawnPoint->SetupAttachment(Root);
}

void AWeapon_AOE::PullTrigger()
{
	Super::PullTrigger();

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
		if (!OwnerController) return;

		OwnerController->GetPlayerViewPoint(Location, Rotation);
		SpawnRotation = Rotation;
	}


	SpawnAOE(HitLocation, SpawnRotation);
}

//FVector AWeapon_AOE::GetSpawnLocation()
//{
//	return AOE_SpawnPoint->GetComponentLocation();
//}

//FRotator AWeapon_AOE::GetSpawnRotation()
//{
//	FRotator SpawnRotation;
//	FVector HitLocation;
//	FHitResult Hit;
//	FVector ShotDirection;
//
//	bool bSuccess = WeaponTrace(Hit, ShotDirection);
//	if (bSuccess)
//	{
//		HitLocation = Hit.Location;
//		SpawnRotation = GetShotRotation(HitLocation);
//	}
//	else
//	{
//		FVector Location;
//		FRotator Rotation;
//
//		AController* OwnerController = GetOwnerController();
//		if (!OwnerController) return SpawnRotation;
//
//		OwnerController->GetPlayerViewPoint(Location, Rotation);
//		return Rotation;
//	}
//
//	return SpawnRotation;
//}

FRotator AWeapon_AOE::GetShotRotation(FVector HitLocation)
{
	FVector Location;
	FRotator Rotation;

	AController* OwnerController = GetOwnerController();
	if (!OwnerController) return Rotation;

	FVector Result;
	Result = HitLocation - (AOE_SpawnPoint->GetComponentLocation());
	Rotation = Result.GetSafeNormal().Rotation();

	return Rotation;
}

bool AWeapon_AOE::WeaponTrace(FHitResult& Hit, FVector& ShotDirection)
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

void AWeapon_AOE::SpawnAOE(FVector Location, FRotator Rotation)
{
	if (AOE_Class)
	{
		AAOE_Base* TempAOE = GetWorld()->SpawnActor<AAOE_Base>(AOE_Class, Location, Rotation);
		TempAOE->SetOwner(this);
		//TempAOE->SetDamage(Damage);
	}
}