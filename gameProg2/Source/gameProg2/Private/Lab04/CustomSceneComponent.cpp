// Fill out your copyright notice in the Description page of Project Settings.


#include "Lab04/CustomSceneComponent.h"

#include "DetailLayoutBuilder.h"

// Sets default values for this component's properties
UCustomSceneComponent::UCustomSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...


	//initialize the local transform
	//if it has no parent
	if(Parent == nullptr)
	{
		//then you initialize it to be the transform of the actor on which this component is connect(ed) to
		setLocalTransform(GetOwner()->GetTransform());
	} else //otherwise, if it has a parent
	{
		//initialize it to the identity
		setLocalTransform(FTransform::Identity);
	}
	
		
}


// Called every frame
void UCustomSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(Parent != nullptr) // if we're at the top of the hierarchy 
	{
		
		FTransform parentTransform = Parent->GetTransform(); //I'm unsure if there's a better way to get the parent's custom local transform
		FTransform finalTransform = LocalTransform * parentTransform;
		GetOwner()->SetActorTransform(finalTransform);
	} else // if we're at the top then we'll just want to set our Unreal transform to our custom local transform
	{
		
		GetOwner()->SetActorTransform(LocalTransform);
	}
	
	
}

void UCustomSceneComponent::setLocalTransform(FTransform newTransform)
{
	setLocalRotation(newTransform.GetRotation());
	setLocalScale(newTransform.GetScale3D());
	setLocalTranslation(newTransform.GetTranslation());
}


void UCustomSceneComponent::setLocalRotation(FQuat newRotation)
{
	LocalTransform.SetRotation(newRotation);
}


void UCustomSceneComponent::setLocalScale(FVector newScale)
{
	LocalTransform.SetScale3D(newScale);
}


void UCustomSceneComponent::setLocalTranslation(FVector newTranslation)
{
	LocalTransform.SetTranslation(newTranslation);
}




