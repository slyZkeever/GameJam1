// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "Camera/CameraComponent.h"

#include "Grabber.h"

#include "Tracer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UTracer : public UActorComponent //Tracer
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTracer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Variable")
	bool DrawDBLine = true;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Class Variable")
	FHitResult HitResult;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Class Variables")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectArray;*/

	UFUNCTION(BlueprintCallable, Category = "Class Function")
	void TraceForInteractives();

	UFUNCTION(BlueprintCallable, Category = "Class Function")
	void SetObjectType(TArray<TEnumAsByte<EObjectTypeQuery>> Value);

	UFUNCTION(BlueprintCallable, Category = "Class Function")
	bool AllowInteraction();

	UFUNCTION()
	void SetTraceStart();

	UFUNCTION()
	void SetTraceEnd();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector TraceStart;
	FVector TraceEnd;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	
	UPROPERTY()
	UGrabber* Grabber = nullptr;

	UPROPERTY()
	UCameraComponent* PlayerCamera = nullptr;
};