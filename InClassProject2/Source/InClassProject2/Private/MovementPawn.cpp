// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementPawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystem.h"
//#include "InClass/InClass.h"

// Sets default values
AMovementPawn::AMovementPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubObject<UStaticMeshComponent>(TEXT("static mesh"));
	
}

// Called when the game starts or when spawned
void AMovementPawn::BeginPlay()
{
	Super::BeginPlay();


	if(TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if(TObjectPtr<ULocalPlayer> localPlayer = Cast<ULocalPlayer>(PlayerConroller->GetLocalPlayer()))
		{
			if(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> inputSystem =
				localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if(!InputMapping.IsNull())
				{
					inputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
				}
			}
		}
	}
}

// Called every frame
void AMovementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	WARN("getting enhanced input component");


	WARN("bingind move action");
	EIS->BindAction(SlideCubeAction, ETriggerEvent::Triggered, this, &AMovementPawn::Move);
};


void AMovementPawn::Move(const struct FInputActionInstance& Instance)
{
	lastInput = Instance.GetValue().Get<FVector2d>();
	LOG("Move input: (&f, &f)", lastInput.X, lastInput.y);
	
}
