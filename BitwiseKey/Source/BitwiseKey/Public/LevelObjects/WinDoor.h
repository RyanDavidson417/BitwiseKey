#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinDoor.generated.h"

class UBoxComponent;
class ABitwiseGameMode;

UCLASS()
class BITWISEKEY_API AWinDoor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWinDoor();

#pragma region Unreal Functions
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#pragma endregion

#pragma region Variables
protected:
	UPROPERTY(VisibleAnywhere, category="Collision")
	TObjectPtr<UBoxComponent> BoxCollider;

	TObjectPtr<ABitwiseGameMode> gm;
#pragma endregion

#pragma region Custom Functions
protected:
	UFUNCTION()
	void BeginOverlapCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion

};
