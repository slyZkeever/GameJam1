 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CalculateWeight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UCalculateWeight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCalculateWeight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
	float AddMass(UPrimitiveComponent* Collider, FName ComponentsTag);

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
	float SubtractMass(AActor* ActorEndOverlap, FName ComponentsTag);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<AActor*> OverlappingActorArray;
	
};
