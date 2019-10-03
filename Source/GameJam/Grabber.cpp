// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
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


	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!MyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Character Not Found!"));
	}
	else
	{
		PlayerCam = MyCharacter->FindComponentByClass<UCameraComponent>();
		if (!PlayerCam)
		{
			UE_LOG(LogTemp, Error, TEXT("Camera Not Found!"));
		}
	}

}

void UGrabber::FindPhysicsHandle() //find "PhysicsHandleComponent" added in BP Class
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Handle Not Found!"));
	}

}



void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstObjectHit();
	
	if (ActorHit)
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		AActor* Actor = HitResult.GetActor();

		if (!PhysicsHandle) return; 

		if (Actor)
		{
		    if (!(ComponentToGrab->IsSimulatingPhysics()))
			{
			    ComponentToGrab->SetSimulatePhysics("true");
			}

		    //ComponentToGrab->SetMaterialByName();
			//UE_LOG(LogTemp, Warning, TEXT("Grabbing object %s"), *(ComponentToGrab->GetName()) );

			PhysicsHandle->GrabComponentAtLocationWithRotation
			(
				ComponentToGrab,
				NAME_None,
				ComponentToGrab->GetOwner()->GetActorLocation(),
				ComponentToGrab->GetOwner()->GetActorRotation()
			);
			
			if (KeyClass && (KeyClass != Actor->GetClass())) //the key from project has defined changes in mat in Bp_Keyhole class 
			{
				if (OnGrabMat)
				{
					ComponentToGrab->SetMaterial(0, OnGrabMat);
				}
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Component Found: %s"), *(ComponentToGrab->GetName()));

			Grabbed = 1;

			UE_LOG(LogTemp, Warning, TEXT("Grabbed is: %d"), Grabbed);
		}
				
	}

}
	

void UGrabber::Drop()
{
	
	if (Grabbed)
	{
		UPrimitiveComponent* ComponentToGrab = GetFirstObjectHit().GetComponent();

		if (ComponentToGrab)
		{
			if (DefaultMat)
			{
				ComponentToGrab->SetMaterial(0, DefaultMat);
			}
		}

		PhysicsHandle->ReleaseComponent();
		Grabbed = 0;

		UE_LOG(LogTemp, Warning, TEXT("Grabbed is: %d"), Grabbed);

	}
	
}

void UGrabber::Throw()
{
	FHitResult HitResult = GetFirstObjectHit();
	
	if (ActorHit)
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		AActor* Actor = HitResult.GetActor();

		if (Actor)
		{
			if (Grabbed)
			{
				//float ForceMagnitude = ForceApplied / (ComponentToGrab->GetMass());

				//UE_LOG(LogTemp, Warning, TEXT("Throwing Object of mass %f with Force: %f"), ComponentToGrab->GetMass(), ForceMagnitude);

				ComponentToGrab->AddImpulse((PlayerCam->GetForwardVector() * ForceApplied), NAME_None, false);

				if (DefaultMat)
				{
					ComponentToGrab->SetMaterial(0, DefaultMat);
				}

				Drop();
			}
		}
	}
}


FHitResult UGrabber::GetFirstObjectHit()
{
	//Crete Query for Collision

	FCollisionQueryParams TraceComp(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	ActorHit = GetWorld()->LineTraceSingleByObjectType( OUT HitResult, GetLineTraceStart(), GetLineTraceEnd(),
                  		                                FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceComp
	                                                  );

	UE_LOG(LogTemp, Warning, TEXT("ActorHit: %d"), ActorHit);
	
	AActor *HitActor = HitResult.GetActor();
	if (HitActor != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Actor Found: %s"), *(HitActor->GetName()) );
	}

	return HitResult;
}

FVector UGrabber::GetLineTraceStart()
{

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	PlayerViewPointLocation = PlayerCam->GetComponentLocation();
	PlayerViewPointRotation = PlayerCam->GetComponentRotation();

	return PlayerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	PlayerViewPointLocation = PlayerCam->GetComponentLocation();
	PlayerViewPointRotation = PlayerCam->GetComponentRotation();

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

void UGrabber::SetGrabbed(bool Value)
{
	Grabbed = Value;
}

bool UGrabber::GetGrabbed()
{
	return Grabbed;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}

}

