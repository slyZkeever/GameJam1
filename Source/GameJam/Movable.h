// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"

#include "Movable.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEJAM_API UMovable : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMovable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClassVars")
		int Rate = 4;

	bool bPlatformAtA = true;

	bool bIncrease = false;

	int DirectionToMove = 1;

	bool bInsideA = false;
	bool bInsideB = false;

	bool bNearBtnA = false;
	bool bNearBtnB = false;



	UFUNCTION(BlueprintCallable, Category = "ClassFuncs")
		int CalculateTime(UStaticMeshComponent* Object1, UStaticMeshComponent* Object2);

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void Switcher();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void setbPlatformAtA(bool Val);
	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbPlatformAtA();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void setbInsideA(bool Val);
	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbInsideA();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void setbInsideB(bool Val);
	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbInsideB();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void setbNearBtnA(bool Val);
	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbNearBtnA();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		void setbNearBtnB(bool Val);
	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbNearBtnB();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		bool getbIncrease();

	UFUNCTION(BlueprintCallable, Category = "Getters/Setters")
		int getDirectionToMove();


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
