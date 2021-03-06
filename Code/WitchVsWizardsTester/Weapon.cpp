// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	bCanFire = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(Flash, Mesh, TEXT("WeaponFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(WeaponSound, Mesh, TEXT("WeaponFlashSocket"));
}

void AWeapon::ResetFire()
{
	bCanFire = true;
	GetWorldTimerManager().ClearTimer(FireDelayTimerHandle);
}

AController* AWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;
	return OwnerPawn->GetController();
}