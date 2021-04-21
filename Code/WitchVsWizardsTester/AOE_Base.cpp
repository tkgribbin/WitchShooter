// Fill out your copyright notice in the Description page of Project Settings.


#include "AOE_Base.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AAOE_Base::AAOE_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	EffectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	EffectMesh->SetupAttachment(Root);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box Mesh"));
	CollisionBox->SetupAttachment(Root);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere Mesh"));
	CollisionSphere->SetupAttachment(Root);

	InitialLifeSpan = Lifespan;
	bIsOverlap = false;
}


// Called when the game starts or when spawned
void AAOE_Base::BeginPlay()
{
	Super::BeginPlay();

	if (bUseBox) 
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAOE_Base::OnBoxBeginOverlap);
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AAOE_Base::OnBoxEndOverlap);
	}
	else
	{
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAOE_Base::OnSphereBeginOverlap);
		CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AAOE_Base::OnSphereEndOverlap);
	}
	
	
}

void AAOE_Base::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapTimerDelegate.BindUFunction(this, FName("DealDamage"), OtherActor, Damage, nullptr, this, DamageType);

	if (OtherActor && OtherActor != this)
	{
		GetWorldTimerManager().SetTimer(OverlapTimerHandle, OverlapTimerDelegate, DamageDelay, true, 0.0f);
		bIsOverlap = true;
		//DealDamage(OtherActor, Damage, nullptr, this, DamageType);
	}
}

void AAOE_Base::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapTimerDelegate.BindUFunction(this, FName("DealDamage"), OtherActor, Damage, nullptr, this, DamageType);

	if (OtherActor && OtherActor != this)
	{
		GetWorldTimerManager().SetTimer(OverlapTimerHandle, OverlapTimerDelegate, DamageDelay, true, 0.0f);
		bIsOverlap = true;
		//DealDamage(OtherActor, Damage, nullptr, this, DamageType);
	}
}

void AAOE_Base::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlap = false;
}

void AAOE_Base::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlap = false;
}

void AAOE_Base::DealDamage(AActor* OtherActor, float DamageAmount, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> ThisDamageType)
{
	if (bIsOverlap) 
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	
}

void AAOE_Base::TimedFunction()
{
	if (!bIsOverlap)
	{
		GetWorldTimerManager().ClearTimer(OverlapTimerHandle);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Apply Damage Now"));
	}
}

void AAOE_Base::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}


//TODO, Damage instead of print string
//		On Collision End, Set isOverlap = false

//Begin Overlap
//Apply Damage & set IsOverlap
//if Continuous, Start Timer
//if Timer Done & IsOverlap, Apply Damage

//End Overlap
//set IsOverlap = false
//Clear Timer