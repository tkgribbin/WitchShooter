// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBeam.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AWeaponBeam::AWeaponBeam()
{
	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Beam Particle"));
	BeamParticle->SetupAttachment(RootComponent);

	BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Beam Target"));
	BeamTarget->SetupAttachment(BeamParticle);
	BeamSource = CreateDefaultSubobject<USceneComponent>(TEXT("Beam Source"));
	BeamSource->SetupAttachment(BeamParticle);

	BeamParticle->SetVectorParameter("Target", BeamTarget->GetComponentLocation());
	BeamParticle->SetVectorParameter("Source", BeamSource->GetComponentLocation());

	BeamParticle->SetVisibility(false);
}

void AWeaponBeam::PullTrigger()
{
	Super::PullTrigger();

	BeamParticle->SetVisibility(true);
	GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &AWeaponBeam::ResetFlash, FlashTime, false);


	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = WeaponTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.Location);
		BeamTarget->SetWorldLocation(Hit.Location);

		if (BeamParticle && BeamSource && BeamTarget) 
		{
			BeamParticle->SetVectorParameter("Target", BeamTarget->GetRelativeLocation());
			BeamParticle->SetVectorParameter("Source", BeamSource->GetRelativeLocation());
		}


		AActor* HitActor = Hit.GetActor();
		if (!HitActor) { return; }
		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		AController* OwnerController = GetOwnerController();
		
		if (!OwnerController) return;
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}
}

void AWeaponBeam::ResetFlash()
{
	BeamParticle->SetVisibility(false);
	GetWorldTimerManager().ClearTimer(FlashTimerHandle);
}

bool AWeaponBeam::WeaponTrace(FHitResult& Hit, FVector& ShotDirection)
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

