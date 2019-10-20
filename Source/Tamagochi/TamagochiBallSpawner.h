// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TamagochiBallSpawner.generated.h"

UCLASS()
class TAMAGOCHI_API ATamagochiBallSpawner : public AActor
{
    GENERATED_BODY()

private:
    int SpawnedBalls = 0;
    UWorld * World;
public:	
	// Sets default values for this actor's properties
	ATamagochiBallSpawner();
    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Numerics)
        int NumberOfBalls;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Numerics)
        TSubclassOf<class AActor> TypeOfActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
