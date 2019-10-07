// Fill out your copyright notice in the Description page of Project Settings.

#include "CalculateWeight.h"
#include "Classes/GameFramework/Actor.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UCalculateWeight::UCalculateWeight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCalculateWeight::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCalculateWeight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


float UCalculateWeight::AddMass(UPrimitiveComponent* Collider, FName ComponentsTag)
{
	//get overlapping actors, set it to an array
	Collider->GetOverlappingActors(OverlappingActorArray, TSubclassOf<AActor>());

	for (int32 i = 0; i != OverlappingActorArray.Num(); ++i)
	{
				
		//get the actor component that has the tag.
		TArray<UActorComponent*>ComponentArray = OverlappingActorArray[i]->GetComponentsByTag(UStaticMeshComponent::StaticClass(), ComponentsTag);
				
		//cast to static mesh component. get mass. add to CalculatedMass. 
		for (int32 i = 0; i != ComponentArray.Num(); ++i)
		{
			UStaticMeshComponent* StaticComponent = Cast<UStaticMeshComponent>(ComponentArray[i]);
			if (StaticComponent)
			{
				CalculatedMass += StaticComponent->GetMass();
			}
		}
	}
		
	return CalculatedMass;
}

float UCalculateWeight::SubtractMass(AActor* ActorEndOverlap, FName ComponentsTag)
{
	int RemovingActorsindex = 0;

	//finding player that left from overlapping array
	if ( OverlappingActorArray.Find(ActorEndOverlap, RemovingActorsindex) )  
	{

		//get the actor component that has the tag.
		TArray<UActorComponent*>ComponentArray = OverlappingActorArray[RemovingActorsindex]->GetComponentsByTag(
			UStaticMeshComponent::StaticClass(), ComponentsTag
		);

		//cast to static mesh component. get mass. add to CalculatedMass. 
		for (int32 i = 0; i != ComponentArray.Num(); ++i)
		{
			UStaticMeshComponent* StaticComponent = Cast<UStaticMeshComponent>(ComponentArray[i]);
			if (StaticComponent)
			{
				CalculatedMass -= StaticComponent->GetMass();
			}
		}
	}

		
	return CalculatedMass;
}
