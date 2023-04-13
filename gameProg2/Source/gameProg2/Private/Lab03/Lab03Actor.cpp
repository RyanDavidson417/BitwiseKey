// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab03/Lab03Actor.h"

// Sets default values
ALab03Actor::ALab03Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALab03Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab03Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

