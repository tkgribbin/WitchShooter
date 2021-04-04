// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInstant.h"
#include "Kismet/GameplayStatics.h"

AWeaponInstant::AWeaponInstant()
{

}

void AWeaponInstant::PullTrigger()
{
	Super::PullTrigger();

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = WeaponTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if (!HitActor) { return; }
		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		AController* OwnerController = GetOwnerController();
		if (!OwnerController) return;
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
}

bool AWeaponInstant::WeaponTrace(FHitResult& Hit, FVector& ShotDirection)
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

