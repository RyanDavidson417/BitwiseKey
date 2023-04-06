// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab02Actor.h"

#include "BPLibInClass.h"

// Sets default values
ALab02Actor::ALab02Actor() : speed(100)
{
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//anything that's a C++ class, needs to use CreateDefaultSubobject
	TheMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//all this has to happen in the constructor
	TheMesh -> SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_cube"));
	//for everything that's an an asset, we use FObjectFinder

	if(CubeVisualAsset.Succeeded())
	{
		TheMesh->SetStaticMesh(CubeVisualAsset.Object);
		TheMesh->SetRelativeLocation(InitialPosition);
		
	}
	
}

// Called when the game starts or when spawned
void ALab02Actor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALab02Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	
	NewLocation.Z += DeltaHeight * speed;
	SetActorLocation(NewLocation);

	
	//float DeltaRotation = DeltaTime * 20.0f;
	//NewRotation.Yaw += DeltaRotation
	//SetActorLocationAndRotation(NewLocation, NewRotation);
	
	// UBPLibInClass::MoveTowards()

	//GetOwner()->SetActorLocation()//syntax used when called from a component
	//SetActorLocation();
}

