// Fill out your copyright notice in the Description page of Project Settings.


#include "TamagochiBallSpawner.h"
#include "Engine/World.h"

// Sets default values
ATamagochiBallSpawner::ATamagochiBallSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATamagochiBallSpawner::BeginPlay()
{
	Super::BeginPlay();
    World = GetWorld();
}

// Called every frame
void ATamagochiBallSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (SpawnedBalls < NumberOfBalls)
    {
        if (TypeOfActor)
        {
            if (World)
            {
                for (int i = 0; i < 10; i++)
                {
                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = this;
                    FRotator Rotator;
                    FVector Location = this->GetActorLocation();
                    Location.X += rand() % 500;
                    Location.Y += rand() % 500;
                    World->SpawnActor<AActor>(TypeOfActor, Location, Rotator, SpawnParams);
                    SpawnedBalls++;
                }
            }
        }
    }
}


