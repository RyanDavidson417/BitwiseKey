// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/XRayVision.h"
#include "CustomGameMode.h"

UXRayVision::UXRayVision()
{
}

void UXRayVision::BeginPlay()
{
	//gm = (GetWorld()->GetAuthGameMode<ACustomGameMode>()); //should maybe do this as a variable in the .h
	//gm = GetWorld()->GetAuthGameMode();
	//gm = Cast<ACustomGameMode>(gm);
	//ACustomGameMode* gm = (ACustomGameMode*)GetWorld()->GetAuthGameMode();
	gm  = (ACustomGameMode*)GetWorld()->GetAuthGameMode();


}

void UXRayVision::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UXRayVision::Interact(APlayerController* playerController)
{
	UE_LOG(LogTemp, Warning, TEXT("Collected object"));
	//
	if (IsValid(gm)) {
		gm->CollectXRay();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("gm not valid"));
	}
}
