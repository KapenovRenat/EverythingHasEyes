// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PickUpActor.h"
#include "Components/ActorComponent.h"
#include "InventaryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVERYTHINGHASEYES_API UInventaryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventaryComponent();
	
	TArray<APickUpActor*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetItem(APickUpActor* Item);
		
};
