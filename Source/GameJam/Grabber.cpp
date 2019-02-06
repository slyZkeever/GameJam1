// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	AllowInput();
	

}

void UGrabber::FindPhysicsHandle() //find "PhysicsHandleComponent" added in BP Class
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Handle Not Found!"));
	}
	
}

void UGrabber::AllowInput() //find "InputComponent"
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent Not Found!"));
	}
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Throw", IE_Pressed, this, &UGrabber::Throw);
	}
	
}

void UGrabber::Grab()
{
	auto HitResult = GetFirstObjectHit();
	auto ComponentToGrab = HitResult.GetComponent();
	auto Actor = HitResult.GetActor();

	if (Actor)
	{
		if (!PhysicsHandle) { return; }
		else
		{
			if (Grabbed == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Grabbing object"));
				PhysicsHandle->GrabComponentAtLocationWithRotation
				(
					ComponentToGrab, 
					NAME_None, 
					ComponentToGrab->GetOwner()->GetActorLocation(), 
					ComponentToGrab->GetOwner()->GetActorRotation()
				);
				Grabbed = 1;
			}
			else
			{
				if (Grabbed == 1)
				{
					UE_LOG(LogTemp, Warning, TEXT("Releasing object"));
					PhysicsHandle->ReleaseComponent();
					Grabbed = 0;
				}
			}
			
		}
	}
}

void UGrabber::Throw()
{
	auto HitResult = GetFirstObjectHit();
	auto ComponentToGrab = HitResult.GetComponent();
	auto Actor = HitResult.GetActor();

	if (Actor)
	{
		if (Grabbed == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Throwing Object"));
			ComponentToGrab->AddForce(FVector(GetOwner()->GetActorForwardVector()) * Impulse * ComponentToGrab->GetMass(), NAME_None, 1);
			PhysicsHandle->ReleaseComponent();
			Grabbed = 0;
		}
	}
}

FHitResult UGrabber::GetFirstObjectHit()
{
	//Crete Query for Collision

	FCollisionQueryParams TraceComp(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, 
		GetLineTraceStart(), 
		GetLineTraceEnd(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		TraceComp);

	AActor *HitActor = HitResult.GetActor();
	if(HitActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Found: %s"), *(HitActor->GetName()) );
	}

	return HitResult;
}

FVector UGrabber::GetLineTraceStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return;  }
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}

}

