// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickUpActor.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "EHECharacter.generated.h"

UCLASS()
class EVERYTHINGHASEYES_API AEHECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEHECharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="IsLamp")
	bool isLampOn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Meshes")
	UStaticMeshComponent* LampStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Light")
	UPointLightComponent* LampPointLightComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
	UAnimMontage* AnimMontagePickUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Items")
	TArray<APickUpActor*> Items;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void ToggleLamp();
	void PickUp();
	void SetItem(APickUpActor* Item);
	void ShowItems();
};
