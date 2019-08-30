// Fill out your copyright notice in the Description page of Project Settings.

#include "Movable.h"


// Sets default values for this component's properties
UMovable::UMovable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovable::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMovable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-------------------- getters and setters
void UMovable::setbPlatformAtA(bool Val)
{
	bPlatformAtA = Val;
	UE_LOG(LogTemp, Warning, TEXT("bPlatformAtA = %s"), (bPlatformAtA ? TEXT("true") : TEXT("false")));
}

bool UMovable::getbPlatformAtA()
{
	return bPlatformAtA;
}

void UMovable::setbInsideA(bool Val)
{
	bInsideA = Val;
}

bool UMovable::getbInsideA()
{
	return bInsideA;
}

void UMovable::setbInsideB(bool Val)
{
	bInsideB = Val;
}

bool UMovable::getbInsideB()
{
	return bInsideB;
}

void UMovable::setbNearBtnA(bool Val)
{
	bNearBtnA = Val;
	UE_LOG(LogTemp, Warning, TEXT("bNearBtnA = %s"), (bNearBtnA ? TEXT("true") : TEXT("false")));
}

bool UMovable::getbNearBtnA()
{
	return bNearBtnA;
}

void UMovable::setbNearBtnB(bool Val)
{
	bNearBtnB = Val;
	UE_LOG(LogTemp, Warning, TEXT("bNearBtnB = %s"), (bNearBtnB ? TEXT("true") : TEXT("false")));
}

bool UMovable::getbNearBtnB()
{
	return bNearBtnB;
}

bool UMovable::getbIncrease()
{
	return bIncrease;
}

int UMovable::getDirectionToMove()
{
	return DirectionToMove;
}
//-----------------------

void UMovable::CalculateTime(UStaticMeshComponent* Object1, UStaticMeshComponent* Object2)
{
	MaxTime = UKismetMathLibrary::FTrunc
	(
		(Object1->GetRelativeTransform().GetLocation().Z) - (Object2->GetRelativeTransform().GetLocation().Z)
	) / Rate;

}

void UMovable::Switcher()
{
	
	if (bPlatformAtA && bInsideA)
	{
		DirectionToMove = 1;
		bIncrease = true;
		
		UE_LOG(LogTemp, Warning, TEXT("Direction = %d, bIncrease = %s"), 
			DirectionToMove, (bIncrease ? TEXT("true") : TEXT("false")));
	}

	else
	{
		if (!bPlatformAtA && bInsideA)
		{
			DirectionToMove = -1;
			bIncrease = false;
			
			UE_LOG(LogTemp, Warning, TEXT("Direction = %d, bIncrease = %s"), 
				DirectionToMove, (bIncrease ? TEXT("true") : TEXT("false")) );
		}

		else
		{
			if (bPlatformAtA && bInsideB)
			{
				DirectionToMove = 1;
				bIncrease = true;
				
				UE_LOG(LogTemp, Warning, TEXT("Direction = %d, bIncrease = %s"), 
					DirectionToMove, (bIncrease ? TEXT("true") : TEXT("false")) );
			}

			else
			{
				if (!bPlatformAtA && bInsideB)
				{
					DirectionToMove = -1;
					bIncrease = false;
					
					UE_LOG(LogTemp, Warning, TEXT("Direction = %d, bIncrease = %s "), 
						DirectionToMove, (bIncrease ? TEXT("true") : TEXT("false")) );
				}
			}
		}
	}
}

void UMovable::PerformAnimation(UStaticMeshComponent* Platform)
{
	if (bNearBtnA || bNearBtnB)
	{
		FVector NewLocation = Platform->GetRelativeTransform().GetLocation();
		
		if (bIncrease && (CurrentTime <= MaxTime))
		{
			CurrentTime += ASecond;
			Platform->SetRelativeLocation( FVector(NewLocation.X, NewLocation.Y, (NewLocation.Z + Rate*DirectionToMove) ));
		}

		if (!bIncrease && (CurrentTime >= 0))
		{
			CurrentTime -= ASecond;
			Platform->SetRelativeLocation( FVector(NewLocation.X, NewLocation.Y, (NewLocation.Z + Rate*DirectionToMove) ));
		}
	}
	
}
