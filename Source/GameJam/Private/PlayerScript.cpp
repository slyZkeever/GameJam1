// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerScript.h"

#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"	




// Sets default values for this component's properties
UPlayerScript::UPlayerScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerScript::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerScript::TraceByChannel()
{
	FCollisionQueryParams CollisionQueryParams(FName(TEXT("MyTraceTag")), false, GetOwner());
	
	
	GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, TraceChannel, CollisionQueryParams);

	if (DrawDBLine)
	{
		if (HitResult.bBlockingHit) DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, LifeTime);

		if (!HitResult.bBlockingHit) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, LifeTime);
	}
	
}

void UPlayerScript::setStart(FVector val)
{
	Start = val;
}

void UPlayerScript::setEnd(FVector val)
{
	End = val;
}

void UPlayerScript::setTraceChannel(ECollisionChannel val)
{
	TraceChannel = val;

	//UE_LOG(LogTemp, Warning, TEXT("TraceChannel: %d"), TraceChannel);
}


// Called every frame
void UPlayerScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceByChannel();
}

