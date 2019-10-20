// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TamagochiCharacter.generated.h"

UENUM(BlueprintType)
enum class StatType : uint8
{
    Hunger,
    Thrist,
    Social,
    Fun
};

UCLASS(Blueprintable)
class ATamagochiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATamagochiCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

    /**Stats */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
        float Health;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
        float Hunger;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
        float Thirst;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
        float Social;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
        float Fun;

    /** Stat Regeneration Multipliers*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float HungerUpMod = 20.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float ThirstUpMod = 30.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float SocialUpMod = 20.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float FunUpMod = 40.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float HungerDownMod = 10.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float ThirstDownMod = 15.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float SocialDownMod = 10.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float FunDownMod = 20.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        float HealthDownMod = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Target")
        int TargetID;

    UFUNCTION(BlueprintImplementableEvent, Category = "Game_Over")
        void Game_Over();

private:

    /** Stat Regeneration Bools*/
    bool HungerRegen = false;
    bool ThirstRegen = false;
    bool SocialRegen = false;
    bool FunRegen = false;

    /** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

    /** Functions to handle Stat regeneration */
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void StartRegen(StatType value);
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void StopRegen(StatType value);

    void UpdateStats(float dt);

};

