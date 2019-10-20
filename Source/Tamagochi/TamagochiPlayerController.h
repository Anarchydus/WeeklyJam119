// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Animation/AnimSequence.h"
#include "TamagochiPlayerController.generated.h"

UCLASS()
class ATamagochiPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATamagochiPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
    bool bMoveCamera = false;
    bool bcameraMoved = false;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the given world location. */
    UFUNCTION(BlueprintCallable, Category = Movement)
    void SetNewMoveToActorDestination(const AActor* target_zone);

    /** Camera Zoom Functions */
    void ZoomIn();
    void ZoomOut();
    void MoveCamera();
    void ReturnCamera();

};


