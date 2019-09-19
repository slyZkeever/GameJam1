// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnableManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
USpawnableManager::USpawnableManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnableManager::BeginPlay()
{
	Super::BeginPlay();

	//TArray<SpawnActorClass> ActorArray;
	//UE_LOG(LogTemp, Warning, TEXT("Actor Array's size: %d"), SpawnActorArray.Num() );
	
}



// Called every frame
void USpawnableManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnableManager::SpawnInteractables( UPrimitiveComponent* SpawnCollider)
{
	if (SpawnCollider && SpawnActorClass)
	{
		AActor* Actor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnCollider->GetComponentTransform());
		
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());

		SpawnActorArray.Add(Actor);
		UStaticMeshComponent* Mesh = Actor->FindComponentByClass<UStaticMeshComponent>();
		Mesh->SetSimulatePhysics(true);
		Mesh->SetMassOverrideInKg(NAME_None, CubeMass, true);
	}
}

void USpawnableManager::DeleteInteractables()
{
	bool Removed = false;
	int32 DelIdx = -1;

	for (int32 i = SpawnActorArray.Num() -1 ; i != -1; i--)
	{
		//UE_LOG(LogTemp, Warning, TEXT("index: %d"), i);

		if(SpawnActorArray[i]->FindComponentByClass<UStaticMeshComponent>()->IsSimulatingPhysics()) //sim physics 1 = not attached
		{
			UE_LOG(LogTemp, Warning, TEXT("Deleting Actor: %s"), *SpawnActorArray[i]->GetName());
			UE_LOG(LogTemp, Warning, TEXT("index: %d"), i);		

			DelIdx = i; //remove earliest object that still sim physics
			Removed = true;
		}

	}

	if (Removed)
	{
		if (!SpawnActorArray[DelIdx]) return;

		if (!SpawnActorArray[DelIdx]->IsValidLowLevel()) return;

		SpawnActorArray[DelIdx]->K2_DestroyActor();

		SpawnActorArray.RemoveAt(DelIdx);
	}

	if ( !Removed)
	{
		if (!SpawnActorArray[0]) return;

		if (!SpawnActorArray[0]->IsValidLowLevel()) return;

		SpawnActorArray[0]->K2_DestroyActor();

		SpawnActorArray.RemoveAt(0);

		Removed = true;
	}

}

int USpawnableManager::GetArrayLength()
{
	return SpawnActorArray.Num();
}
