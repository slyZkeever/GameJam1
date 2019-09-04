// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "UObject/Class.h"

#include "SpawnableManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API USpawnableManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnableManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
	int32 NumberOfCopies = 3;
	
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
	void ManageInteractables(UClass* SpawningActorsClass, TArray<AActor*> ObjectToSpawn, UBoxComponent* CollisionVol);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
