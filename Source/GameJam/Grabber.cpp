// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"



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
	HitResult = GetFirstObjectHit();
	ComponentToGrab = HitResult.GetComponent();
	Actor = HitResult.GetActor();

	if (Grabbed == 0)
	{
		if (!PhysicsHandle) { return; }
		else
		{
			if (Actor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Grabbing object"));
				PhysicsHandle->GrabComponentAtLocationWithRotation
				(
					ComponentToGrab, 
					NAME_None, 
					ComponentToGrab->GetOwner()->GetActorLocation(), 
					ComponentToGrab->GetOwner()->GetActorRotation()
				);
				if (!(ComponentToGrab->IsSimulatingPhysics()))
				{
					ComponentToGrab->SetSimulatePhysics(1);
				}
				Grabbed = 1;
			}
			else
			{
				if (Grabbed == 1)
				{
					Drop();
				}
			}
			
		}
	}
}

void UGrabber::Drop()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing object"));
	PhysicsHandle->ReleaseComponent();
	Grabbed = 0;
}

void UGrabber::Throw()
{
	if (Grabbed == 1)
	{
		if (Actor)
		{
			float ForceMagnitude = ForceApplied / (ComponentToGrab->GetMass());
			UE_LOG(LogTemp, Warning, TEXT("Throwing Object of mass %f with Force: %f"), ComponentToGrab->GetMass(), ForceMagnitude);
			ComponentToGrab->AddForce( (PlayerCam->GetForwardVector() * ForceMagnitude), NAME_None, 1);
			Drop();
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

