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

	UE_LOG(LogTemp, Warning, TEXT("Actor Array's size: %d"), SpawnActorArray.Num() );
	
}



// Called every frame
void USpawnableManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USpawnableManager::ManageInteractables(UBoxComponent* CollisionVol)
{
	// create an array of BpInteractable object
	TArray<SpawnActorClass>
	/*if (SpawnActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("BP Class Name: %s"), *SpawningActorsClass->GetName());
		TArray<SpawnActor> ActorArray;
	}*/

	// chk if the length of array is less or equals to NumberOfCopies-1
	
	//if yes, spawn an interactable at CollisionVol's location 
	
	//if no, chk for the interactable that is still simulating physics. if none is sim physics, del 1st one.
	   
}