// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "PaperSpriteComponent.h"

// Sets default values
ATurret::ATurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));

	TurretSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurretSprite"));
	TurretSprite->TranslucencySortPriority = 1;
	TurretSprite->SetupAttachment(TurretDirection);

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("Turret sprite pos: (%f , %f)"), TurretSprite->GetComponentLocation().X, TurretSprite->GetComponentLocation().Y);
	// UE_LOG(LogTemp, Warning, TEXT("Turrer actor pos: (%f , %f)"), GetActorLocation().X, GetActorLocation().Y);

}

