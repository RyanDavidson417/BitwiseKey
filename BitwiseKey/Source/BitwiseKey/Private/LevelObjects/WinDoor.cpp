#include "LevelObjects/WinDoor.h"
#include "Components/BoxComponent.h"
#include "BitwiseKey/BitwiseKey.h"
#include "Core/BitwiseGameMode.h"

// Sets default values
AWinDoor::AWinDoor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);
}

// Called when the game starts or when spawned
void AWinDoor::BeginPlay()
{
	Super::BeginPlay();

	gm = GetWorld()->GetAuthGameMode<ABitwiseGameMode>();

	BoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWinDoor::BeginOverlapCallback);
}

// Called every frame
void AWinDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWinDoor::BeginOverlapCallback(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	LOG("HELLO")
	if (IsValid(gm)) {
		gm->WinGame();
	} else {
		LOG("NOT VALID")
	}
}
