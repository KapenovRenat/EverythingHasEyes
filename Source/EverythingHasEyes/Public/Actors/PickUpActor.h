// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UENUM(BlueprintType)
enum class EType : uint8
{
	notes     UMETA(DisplayName = "Notes"),
	objects      UMETA(DisplayName = "Objects"),
};

USTRUCT(BlueprintType)
struct FPickUpStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Name")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Type")
	EType Type;
};

UCLASS()
class EVERYTHINGHASEYES_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();
	USceneComponent* RootComponent;
  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Options")
	FPickUpStruct PickUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Variables")
	bool inTrigger;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetupMyPlayerInputComponent(UInputComponent* InputMyComponent);
	void FunctionGetItem();

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
