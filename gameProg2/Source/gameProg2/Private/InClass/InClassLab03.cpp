// Fill out your copyright notice in the Description page of Project Settings.


#include "InClassLab03.h"

// #include "InClass03ActorComponent.h"
// #include "InClass03SceneComponent.h"

// Sets default values
AInClassLab03::AInClassLab03()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject<UInClass03ActorComponent>(TEXT("InClassComponent"));

	
}

// Called when the game starts or when spawned
void AInClassLab03::BeginPlay()
{
	Super::BeginPlay();

	DynamicClass03Component->RegisterComponent();

	// ScenComponent - CreateDefaultSubObject<UInClass03SceneComponent>(this, TEXT("SceneComponent"));
}

// Called every frame
void AInClassLab03::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Dynamic03Component =  NewObject<UInClass03ActorComponent>(this, TEXT("Dynamic InClassComponent"));
}

