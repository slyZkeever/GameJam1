// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Camera/CameraComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInterface.h"
#include "UObject/NameTypes.h"
#include "Templates/SubclassOf.h" 	
#include "Engine/EngineTypes.h"
#include "Math/Vector.h"

#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEJAM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		float Reach = 160.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		int32 ForceApplied = 200000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		FName TagForInteraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		UMaterialInterface* DefaultMat = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		UMaterialInterface* OnGrabMat = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ClassVars")
		TSubclassOf<AActor>KeyClass;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindPhysicsHandle();

	FHitResult GetFirstObjectHit();

	FVector GetLineTraceStart();
	FVector GetLineTraceEnd();

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void Grab();
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void Drop();
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void Throw();
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void SetGrabbed(bool Value);
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		bool GetGrabbed();

private:

	bool Grabbed = false;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UPROPERTY()
	ACharacter* MyCharacter = nullptr;
	
	UPROPERTY()
	UCameraComponent* PlayerCam = nullptr;

	bool ActorHit = false;

};
