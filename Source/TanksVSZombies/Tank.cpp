// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "PaperSpriteComponent.h"


void FTankInput::Sanitize() {
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveX(float AxisValue) {
	RawMovementInput.X += AxisValue;
}

void FTankInput::MoveY(float AxisValue) {
	RawMovementInput.Y += AxisValue;
}


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
	}

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
	TankDirection->SetupAttachment(RootComponent);

	TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
	TankSprite->TranslucencySortPriority = 0;
	TankSprite->SetupAttachment(TankDirection);

	ChildTurret = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret"));
	ChildTurret->SetupAttachment(TankDirection);

	// SpringArmComponent

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 1024.0f;
	CameraComponent->AspectRatio = 4.0f / 3.0f;
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetWorldRotation(FRotator(-0.0f, -90.0f, 0.0f));
	CameraComponent->SetWorldLocation(FVector(0.0f, 0.0f, 300.0f));

	// Initials values
	MoveSpeed = 100.0f;
	MoveAccel = 200.0f;
	YawSpeed = 180.0f;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankInput.Sanitize();
	// UE_LOG(LogTemp, Warning, TEXT("Movement: (%f %f)"), TankInput.MovementInput.X, TankInput.MovementInput.Y);

	// Tank movement logic
	{
		// Move Y (forward and backward movement)
		{
			FVector MovementDirection = TankDirection->GetForwardVector();
			FVector Pos = GetActorLocation();
			Pos += MovementDirection * MoveSpeed * DeltaTime * TankInput.MovementInput.Y;
			SetActorLocation(Pos);
		}

		// Move X (rotation)
		{
			FRotator Rot = GetActorRotation();
			Rot.Yaw += YawSpeed * DeltaTime * TankInput.MovementInput.X;
			SetActorRotation(Rot);
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
}

void ATank::MoveX(float AxisValue) {
	TankInput.MoveX(AxisValue);
}

void ATank::MoveY(float AxisValue) {
	TankInput.MoveY(AxisValue);
}

