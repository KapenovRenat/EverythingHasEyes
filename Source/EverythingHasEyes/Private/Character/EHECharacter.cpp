// Fill out your copyright notice in the Description page of Project Settings.


#include "EverythingHasEyes/Public/Character/EHECharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/InventaryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEHECharacter::AEHECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
	LampStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("LampComponent");
	LampStaticMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "lampSocket");
	LampPointLightComponent = CreateDefaultSubobject<UPointLightComponent>("LampLight");
	LampPointLightComponent->SetupAttachment(LampStaticMeshComponent);
}

// Called when the game starts or when spawned
void AEHECharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterMovement() != nullptr && LampStaticMeshComponent != nullptr && LampPointLightComponent != nullptr)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		LampStaticMeshComponent->SetVisibility(false);
		LampPointLightComponent->SetVisibility(false);
	}
}

// Called every frame
void AEHECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEHECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AEHECharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AEHECharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AEHECharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AEHECharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEHECharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AEHECharacter::StopJumping);
	PlayerInputComponent->BindAction("ShowLamp", IE_Pressed, this, &AEHECharacter::ToggleLamp);
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &AEHECharacter::ShowItems);
}

void AEHECharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEHECharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AEHECharacter::ToggleLamp()
{
	
	UInventaryComponent* InventaryComponent = Cast<UInventaryComponent>(GetComponentByClass(UInventaryComponent::StaticClass()));

	if (InventaryComponent)
	{
		TArray<APickUpActor*> InventaryItems = InventaryComponent->Items;
		int32 Index = InventaryItems.IndexOfByPredicate([](APickUpActor* FindItem){
			return FindItem->PickUp.Names == ETypeNames::NeonLamp;
		});
		
		if (Index >= 0 && InventaryItems[Index]->PickUp.Count > 0)
		{
			if (isLampOn)
			{
				isLampOn = false;
				GetCapsuleComponent()->SetCapsuleRadius(34);
				LampStaticMeshComponent->SetVisibility(false);
				LampPointLightComponent->SetVisibility(false);
			} else
			{
				isLampOn = true;
				GetCapsuleComponent()->SetCapsuleRadius(75);
				LampStaticMeshComponent->SetVisibility(true);
				LampPointLightComponent->SetVisibility(true);
			}
		}
	}
}

void AEHECharacter::PickUp()
{
	if (AnimMontagePickUp)
	{
		UE_LOG(LogTemp, Display, TEXT("Montage"));
		PlayAnimMontage(AnimMontagePickUp, 1.5, NAME_None);
	}
}

void AEHECharacter::ShowItems()
{
	UInventaryComponent* InventaryComponent = Cast<UInventaryComponent>(GetComponentByClass(UInventaryComponent::StaticClass()));

	if (InventaryComponent)
	{
		for (APickUpActor* Item : InventaryComponent->Items)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), FString::FromInt(Item->PickUp.Count), true, false, FLinearColor::Red, 1.0f);
		}
	}
}
