// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"

#include "PlayerScript.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEJAM_API UPlayerScript : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerScript();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
		bool DrawDBLine = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
		float LifeTime = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ClassVars")
		FHitResult HitResult;

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void TraceByChannel();

	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void setTraceChannel(ECollisionChannel val);
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void setStart(FVector val);
	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		void setEnd(FVector val);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector Start;
	FVector End;
	ECollisionChannel TraceChannel;
	
};
