// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Components/PrimitiveComponent.h"
#include "Containers/Array.h"
#include "Templates/SubclassOf.h"

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

	UPROPERTY(EditAnywhere, Category = "ClassVars")
		float CubeMass = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		TSubclassOf<class AActor> SpawnActorClass;

	TArray<AActor*> SpawnActorArray;

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
	    void SpawnInteractables( UPrimitiveComponent* SpawnCollider);

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void DeleteInteractables();

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
	    int GetArrayLength();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
