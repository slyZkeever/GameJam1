// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
		float Reach = 160.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
		int ForceApplied = 200000;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindPhysicsHandle();

	void AllowInput();
	
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
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	bool Grabbed = 0;

	/*FHitResult HitResult;
	UPrimitiveComponent *ComponentToGrab = nullptr;
	AActor *Actor = nullptr;*/

	ACharacter* MyCharacter = nullptr;

	UCameraComponent* PlayerCam = nullptr;
	
};
