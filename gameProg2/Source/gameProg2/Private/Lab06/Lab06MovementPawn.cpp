// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab06/Lab06MovementPawn.h"
#include "EnhancedInputComponent.h"

// Sets default values
ALab06MovementPawn::ALab06MovementPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

	//setting up the actual cube mesh on the static mesh component
	auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/labs/lab06/MyCube.MyCube"));
	if(mesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(mesh.Object);
	}

	auto moveAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/labs/lab06/UserInput/IA_Moving.IA_Moving"));
	if(moveAction.Succeeded())
	{
		MovementAction = moveAction.Object;
	}
	
	auto steerAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/labs/lab06/UserInput/IA_steering.IA_steering"));
	if(steerAction.Succeeded())
	{
		SteeringAction = steerAction.Object;
	}
}

// Called when the game starts or when spawned
void ALab06MovementPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALab06MovementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALab06MovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

