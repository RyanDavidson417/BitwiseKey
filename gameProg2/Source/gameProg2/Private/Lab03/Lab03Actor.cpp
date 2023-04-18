// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab03/Lab03Actor.h"


// Sets default values
ALab03Actor::ALab03Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	PrimaryActorTick.bCanEverTick = true;
	
	// StaticMesh is a UPROPERTY we defined with type TObjectPtr<UStaticMeshComponent>
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SceneComponent  = CreateAbstractDefaultSubobject<ULab03SceneComponent>(TEXT("Lab03SceneComponent"));
	SetRootComponent(SceneComponent);

	
	
	// we let C++ figure out the exact type, but call this templated function--the object created
	// will hold a UStaticMesh in it if it's loaded properly
	///Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'
	const auto mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (mesh.Succeeded())
	{
		// now attach this to our static mesh component
		StaticMesh->SetStaticMesh(mesh.Object);
		// and add it to the root component, using the relative transform
		StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		// and reset its rotation and location to be 0
		StaticMesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FQuat::Identity);
	}
	else
	{
		// NOTE: the following is a macro, it won't work unless you defined it
		//WARN("Unable to load the cube properly");
	}
	
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
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	

	

}

