// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TamagochiCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATamagochiCharacter::ATamagochiCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

    //Intialize Stats, the closer to 0 the worse it is
    Health = 1000;
    Hunger = 1000;
    Thirst = 1000;
    Social = 1000;
    Fun = 300;
}

void ATamagochiCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}

    UpdateStats(DeltaSeconds);
}

void ATamagochiCharacter::StartRegen(StatType value)
{
  
    switch (value)
    {
    case StatType::Hunger:
        if (!HungerRegen)
            HungerRegen = true;
        break;
    case StatType::Thrist:
        if (!ThirstRegen)
            ThirstRegen = true;
        break;
    case StatType::Social:
        if (!SocialRegen)
            SocialRegen = true;
        break;
    case StatType::Fun:
        if (!FunRegen)
            FunRegen = true;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("The Value passed to ATamagochiCharacter::StartRegen was not valid"))
            break;
    }
}

void ATamagochiCharacter::StopRegen(StatType value)
{

    switch (value)
    {
    case StatType::Hunger:
        if (HungerRegen)
            HungerRegen = false;
        break;
    case StatType::Thrist:
        if (ThirstRegen)
            ThirstRegen = false;
        break;
    case StatType::Social:
        if (SocialRegen)
            SocialRegen = false;
        break;
    case StatType::Fun:
        if (FunRegen)
            FunRegen = false;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("The Value passed to ATamagochiCharacter::StopRegen was not valid"))
            break;
    }
}

void ATamagochiCharacter::UpdateStats(float dt)
{
    if (HungerRegen)
      Hunger =  FMath::Clamp(Hunger += HungerUpMod * dt, 0.f, 1000.f);
    else
       Hunger = FMath::Clamp(Hunger -= HungerDownMod * dt, 0.f, 1000.f);

    if (ThirstRegen)
       Thirst = FMath::Clamp(Thirst += ThirstUpMod * dt, 0.f, 1000.f);
    else
       Thirst = FMath::Clamp(Thirst -= ThirstDownMod * dt, 0.f, 1000.f);

    if (SocialRegen)
       Social = FMath::Clamp(Social += SocialUpMod * dt, 0.f, 1000.f);
    else
       Social = FMath::Clamp(Social -= SocialDownMod * dt, 0.f, 1000.f);

    if (FunRegen)
        Fun = FMath::Clamp(Fun += FunUpMod * dt, 0.f, 1000.f);
    else
        Fun = FMath::Clamp(Fun -= FunDownMod * dt, 0.f, 1000.f);

    if (Hunger == 0.f || Thirst == 0.f || Social == 0.f || Fun == 0.f)
        Health = FMath::Clamp(Health -= HealthDownMod * dt, 0.f, 1000.f);

    if (Health == 0.f)
        Game_Over();
}