// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsActor.generated.h"

UCLASS()
class GAMEPROG2_API APhysicsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlapBob(AActor *OverlappedActor, AActor *OtherActor);
	UFUNCTION()
	virtual void OnEndOverlapBob(AActor *OverlappedActor, AActor *OtherActor);
	UFUNCTION()
	virtual void OnHitBob(AActor *OverlappedActor, AActor *OtherActor,
		FVector NormalImpulse, const FHitResult &Hit);

};
