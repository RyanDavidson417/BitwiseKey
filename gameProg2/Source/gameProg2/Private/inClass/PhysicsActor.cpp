// Fill out your copyright notice in the Description page of Project Settings.


#include "inClass/PhysicsActor.h"

// Sets default values
APhysicsActor::APhysicsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the base object and attach it to root
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	SetRootComponent(BaseMeshComponent);

	//assign our function to be the callback
	OnActorBeginOverlap.AddDynamic(this, &APhysicsActor::OnBeginOverlapBob);

}

// Called when the game starts or when spawned
void APhysicsActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

void APhysicsActor::OnBeginOverlapBob(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOveralp Called!"));
}

void APhysicsActor::OnEndOverlapBob(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEndOveralp Called!"));
}

void APhysicsActor::OnHitBob(AActor* OverlappedActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginHit Called!"));
}

