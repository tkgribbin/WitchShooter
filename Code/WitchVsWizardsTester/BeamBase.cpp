// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABeamBase::ABeamBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InitialLifeSpan = Lifespan;

	BeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Beam Particle"));
	BeamParticle->SetupAttachment(RootComponent);
	

	BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Beam Target"));
	BeamTarget->SetupAttachment(RootComponent);
	
	BeamParticle->SetVectorParameter("Target", BeamTarget->GetComponentLocation());
	BeamParticle->SetVectorParameter("Source", BeamTarget->GetComponentLocation());
}

// Called when the game starts or when spawned
void ABeamBase::BeginPlay()
{
	Super::BeginPlay();

	
}


