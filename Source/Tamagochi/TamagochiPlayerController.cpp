// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "TamagochiPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "TamagochiCharacter.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

ATamagochiPlayerController::ATamagochiPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATamagochiPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATamagochiPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
    InputComponent->BindAction("ZoomIn",IE_Pressed, this, &ATamagochiPlayerController::ZoomIn);
    InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ATamagochiPlayerController::ZoomOut);
}

void ATamagochiPlayerController::SetNewMoveToActorDestination(const AActor* target_zone)
{       
        float const Distance = FVector::Dist(target_zone->GetActorLocation(), GetPawn()->GetActorLocation());
        if (Distance > 120.0f)
        {
            UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, target_zone->GetActorLocation());
        }
}

void ATamagochiPlayerController::ZoomIn()
{
    ATamagochiCharacter* myPawn = Cast<ATamagochiCharacter>(GetPawn());
    USpringArmComponent* cameraArm = myPawn->GetCameraBoom();
    cameraArm->TargetArmLength = cameraArm->TargetArmLength+50.f;
}

void ATamagochiPlayerController::ZoomOut()
{

    ATamagochiCharacter* myPawn = Cast<ATamagochiCharacter>(GetPawn());
    USpringArmComponent* cameraArm = myPawn->GetCameraBoom();
    cameraArm->TargetArmLength = cameraArm->TargetArmLength-50.f;
}

void ATamagochiPlayerController::MoveCamera()
{

}

void ATamagochiPlayerController::ReturnCamera()
{

}