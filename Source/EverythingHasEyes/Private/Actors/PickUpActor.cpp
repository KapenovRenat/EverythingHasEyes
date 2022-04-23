// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickUpActor.h"

#include "Character/EHECharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APickUpActor::APickUpActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Mesh->SetupAttachment(GetRootComponent());
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUpActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APickUpActor::OnEndOverlap);
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickUpActor::SetupMyPlayerInputComponent(UInputComponent* InputMyComponent)
{
	InputMyComponent->BindAction("Interact", IE_Pressed, this, &APickUpActor::FunctionGetItem);
}

void APickUpActor::FunctionGetItem()
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Interact", true, false, FLinearColor::Red, 1.0f);
	AEHECharacter* Character = Cast<AEHECharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Character)
	{
		Character->SetItem(this);
		Destroy();
	}
}

void APickUpActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
                                  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Entered", true, false, FLinearColor::Red, 1.0f);
	if (OverlappedComp != nullptr && Other != nullptr && OtherComp != nullptr)
	{
		inTrigger = true;
		EnableInput(GetWorld()->GetFirstPlayerController());
		UInputComponent* MyInputComponent = this->InputComponent;
		if (MyInputComponent) SetupMyPlayerInputComponent(MyInputComponent);
	}
}

void APickUpActor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Exited", true, false, FLinearColor::Red, 1.0f);
	if (OverlappedComp != nullptr && Other != nullptr && OtherComp != nullptr)
	{
		inTrigger = false;
		DisableInput(GetWorld()->GetFirstPlayerController());
	}
}

