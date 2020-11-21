// Fill out your copyright notice in the Description page of Project Settings.

#include "Tracer.h"

#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"	




// Sets default values for this component's properties
UTracer::UTracer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTracer::BeginPlay()
{
	Super::BeginPlay();

	Grabber = GetOwner()->FindComponentByClass<UGrabber>();

	if (!Grabber)
		UE_LOG(LogTemp, Warning, TEXT("Grabber Not Found"))

	PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
	
	if(!PlayerCamera)
		UE_LOG(LogTemp, Warning, TEXT("Camera Not Found"))
}


void UTracer::TraceForInteractives()
{
	SetTraceStart();
	SetTraceEnd();
	
	FCollisionQueryParams QueryParams(FName(TEXT("MyTraceTag")), false, GetOwner());
		
	//GetWorld()->LineTraceSingleByChannel(OUT HitResult, TraceStart, TraceEnd, TraceChannel, QueryParams);

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult, TraceStart, TraceEnd, 
		                                    FCollisionObjectQueryParams(ObjectType), QueryParams);
	/*if(HitResult.bBlockingHit)
		UE_LOG(LogTemp, Warning, TEXT("HitComponent: %s"), *(HitResult.GetComponent()->GetName()))
	*/

	if (DrawDBLine)
	{		
		if (HitResult.bBlockingHit) DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 5.f);

		if (!HitResult.bBlockingHit) DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 5.f);
	}
	
}


bool UTracer::AllowInteraction()
{
	if (Grabber->GetGrabbed())
		return false;

	//UE_LOG(LogTemp, Warning, TEXT("Object Type: %d"), HitResult.GetComponent()->GetCollisionObjectType())
	
	if (HitResult.GetComponent()->GetCollisionObjectType() == ECC_PhysicsBody)
	{
		if (HitResult.GetComponent()->GetMass() > Grabber->GetPickUpLimit())
			return false;
	}

	// Check Actor Under Player
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());

	FHitResult ThisHitResult;

	GetWorld()->LineTraceSingleByObjectType(OUT ThisHitResult, TraceStart,
		TraceStart + (GetOwner()->GetActorUpVector() * (-200)),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), QueryParams);

	if (ThisHitResult.bBlockingHit && ThisHitResult.GetActor() == HitResult.GetActor())
		return false;

	return true;
}


void UTracer::SetTraceStart()
{
	if (!PlayerCamera) return;

	TraceStart = PlayerCamera->GetComponentLocation();
}


void UTracer::SetTraceEnd()
{
	if (!Grabber || !PlayerCamera) return;

	TraceEnd = TraceStart + PlayerCamera->GetForwardVector() * Grabber->GetReach();
}


void UTracer::SetObjectType(TArray<TEnumAsByte<EObjectTypeQuery>> Value)
{
	ObjectType = Value;

	//UE_LOG(LogTemp, Warning, TEXT("TraceChannel: %d"), TraceChannel);
}


// Called every frame
void UTracer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}