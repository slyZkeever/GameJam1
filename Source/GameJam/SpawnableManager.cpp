// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnableManager.h"


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

	
	
}



// Called every frame
void USpawnableManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USpawnableManager::ManageInteractables(UClass* SpawningActorsClass, TArray<AActor*> ObjectToSpawn, UBoxComponent* CollisionVol)
{
	//UE_LOG(LogTemp, Warning, TEXT("Class Name: %s "), *SpawningActorsClass->GetName() );
	
	

	
	// chk if the length of array is less or equals to 2
	
	if (ObjectToSpawn.Num() <= 2)
	{
		auto Aktor = GetWorld()->SpawnActor(SpawningActorsClass, &CollisionVol->GetRelativeTransform(), FActorSpawnParameters() );
		UE_LOG(LogTemp, Warning, TEXT("Actor Added: %s "), *Aktor->GetName());

	}
	/*else
	{

	}*/

	//if yes, spawn an interactable at var location 
	//if no, chk for the interactable still simulating physics. if none is sim physics, del 1st one.
	   
}