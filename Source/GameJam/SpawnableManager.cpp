// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnableManager.h"
#include "Classes/Components/StaticMeshComponent.h"


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

void USpawnableManager::SpawnInteractables(TArray<AActor*> SpawnActorArr, UPrimitiveComponent* SpawnCollider)
{
	if (SpawnCollider && SpawnActorClass)
	{
		AActor* Actor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnCollider->GetComponentTransform());
		
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *Actor->GetName());

		SpawnActorArr.Add(Actor);
		UStaticMeshComponent* Mesh = Actor->FindComponentByClass<UStaticMeshComponent>();
		Mesh->SetSimulatePhysics(true);
		Mesh->SetMassOverrideInKg(NAME_None, CubeMass, true);
	}
}

void USpawnableManager::DeleteInteractables(TArray<AActor*> SpawnActorArr)
{
	bool Removed = false;

	for (uint8 i = SpawnActorArr.Num(); i >= 0; i--)
	{
		//AActor* Actor = SpawnActorArray[i];
		
		if(SpawnActorArr[i]->FindComponentByClass<UStaticMeshComponent>()->IsSimulatingPhysics() )
		{
			
			if (GetWorld()->DestroyActor(SpawnActorArr[i]))
			{
				SpawnActorArr.Remove(SpawnActorArr[i]);
				Removed = true;
			}
		}

		break;
	}

	if ( !Removed && SpawnActorArr[0]->IsValidLowLevel() )
	{
		
		
		if (GetWorld()->DestroyActor(SpawnActorArr[0]))
		{
			SpawnActorArr.Remove(SpawnActorArr[0]);
			Removed = true;
		}
	}

}