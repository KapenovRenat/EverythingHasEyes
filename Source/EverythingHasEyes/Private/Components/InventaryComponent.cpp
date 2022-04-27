// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventaryComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInventaryComponent::UInventaryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventaryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventaryComponent::SetItem(APickUpActor* Item)
{
	// if (Items.Num() == 0) return;
	
	int32 Index = Items.IndexOfByPredicate([Item](APickUpActor* FindItem){
		return FindItem->PickUp.Names == Item->PickUp.Names;
	});
	
	if (Item)
	{
		if (Index >= 0)
		{
			APickUpActor* NewPickUpEl = Items[Index];
			NewPickUpEl->PickUp.Count += Item->PickUp.Count;
			Items.RemoveAt(Index);
			Items.Add(NewPickUpEl);
			UKismetSystemLibrary::PrintString(GetWorld(), "ElementUpdate", true, false, FLinearColor::Red, 10.0f);
			return;
		}
		
		UKismetSystemLibrary::PrintString(GetWorld(), "ElementAdded", true, false, FLinearColor::Red, 10.0f);
		Items.Add(Item);
	}
}

