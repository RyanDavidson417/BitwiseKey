// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab06/Lab06MovementPawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "gameProg2/gameProg2.h"
#include "EnhancedInputSubsystems.h"
#include "BaseGizmos/GizmoElementShared.h"
#include "Camera/CameraComponent.h"

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

	//for this lab this is attached to the staticMesh, but we'll probably want to set up a proper capsule collider as in the unreal code
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(StaticMesh);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.f, -400.f, 200.f));
	// FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	// auto moveAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/labs/lab06/UserInput/IA_Moving.IA_Moving"));
	// if(moveAction.Succeeded())
	// {
	// 	MovementAction = moveAction.Object;
	// }
	//
	// auto steerAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/labs/lab06/UserInput/IA_steering.IA_steering"));
	// if(steerAction.Succeeded())
	// {
	// 	SteeringAction = steerAction.Object;
	// }
	//
	// auto input = ConstructorHelpers::FObjectFinder<UInputMappingContext>(TEXT("/Game/labs/lab06/UserInput/SteeringMappingContext.SteeringMappingContext"));
	// if(input.Succeeded())
	// {
	// 	InputMapping = input.Object;
	// }
}

// Called when the game starts or when spawned
void ALab06MovementPawn::BeginPlay()
{
	Super::BeginPlay();


	UE_LOG(LogTemp, Warning, TEXT("checking for player controller"));
	UE_LOG(LogTemp, Warning, TEXT("isvalid?  %s"), (IsValid(GetController()) ? TEXT("TRUE") : TEXT("FALSE")))

	//add input mapping context
	if(APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("checking to see if there's a local player"));
		if(ULocalPlayer* localPlayer = Cast<ULocalPlayer>(playerController->GetLocalPlayer()))
		{
			UE_LOG(LogTemp, Warning, TEXT("looking for input system "));
			if(UEnhancedInputLocalPlayerSubsystem* inputSystem =
				localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				UE_LOG(LogTemp, Warning, TEXT("loading inputMapping"));	
				if(InputMapping != nullptr)
				{
					
					UE_LOG(LogTemp, Warning, TEXT("Reached the end of nested ifs"));
					inputSystem->AddMappingContext(InputMapping, 0);
				}
			}
		}
	}


	
}


////////////////////////////////////////////////////////////////  INPUT ////////////////////

void ALab06MovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("running SetupPlayerComponent()"));
	//WARN("getting enhanced input component");
	//doncasting the PlayerInputComponent to be a UEnhancedInputComponent
	UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	//bind the move action
	//WARN("Binding Move actions");
	UE_LOG(LogTemp, Warning, TEXT("binding the move action"));
	EIS->BindAction(MovementAction,  ETriggerEvent::Triggered, this, &ALab06MovementPawn::Move);
	//bind the steer action
	EIS->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ALab06MovementPawn::Steer);

	
	//only doing steering action in this - need to mirror movement
}

// Called every frame
void ALab06MovementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input


//move function to move the pawn
void ALab06MovementPawn::Move(const struct FInputActionInstance& Instance)
{
	lastMoveInput = Instance.GetValue().Get<bool>();
	//LOG("MOVE INPUT: (%f, %f)", lastSteerInput.X, lastSteerInput.Y);
	//UE_LOG(LogTemp, Warning, TEXT("MOVE INPUT detected"));

	float moveMagnitude = (lastMoveInput ? 1 : 0);

	if(Controller != nullptr)
	{
	    //UE_LOG(LogTemp, Warning, TEXT("controller not null"));
		FVector tempVec = GetActorForwardVector() * 100;
		//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, %f"), tempVec.X, tempVec.Y, tempVec.Z, moveMagnitude);
		//AddMovementInput(GetActorForwardVector(), moveMagnitude);

		AddActorWorldOffset(tempVec);
		
	}
	
}

void ALab06MovementPawn::Steer(const FInputActionInstance& Instance)
{
	lastSteerInput = Instance.GetValue().Get<FVector3d>();
	//LOG("MOVE INPUT: (%f, %f)", lastSteerInput.X, lastSteerInput.Y);
	//UE_LOG(LogTemp, Warning, TEXT("Steer input value: %f and %f"), lastSteerInput.X, lastSteerInput.Y);

	if(Controller != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("controller not null"));

		float speed = 60; //do this properly in the .h

		float deltaTime = GetWorld()->GetDeltaSeconds();
		FQuat yawQuat = FQuat(GetActorUpVector(), FMath::DegreesToRadians(speed * lastSteerInput.X) * deltaTime);
		FQuat pitchQuat = FQuat(GetActorRightVector(), FMath::DegreesToRadians(speed * lastSteerInput.Y) * deltaTime);
		FQuat rollQuat = FQuat(GetActorForwardVector(), FMath::DegreesToRadians(speed * lastSteerInput.Z) * deltaTime);

		FQuat spinQuat = yawQuat * pitchQuat * rollQuat;
		
		AddActorWorldRotation(spinQuat);

		
		// AddControllerYawInput(lastSteerInput.X);
		// AddControllerPitchInput(lastSteerInput.Y);
	}
	
	
}
