// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_CreateComponent.h"
#include "Components/StaticMeshComponent.h"

UCT_CreateComponent::UCT_CreateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UMaterialInterface> tmpMat1(TEXT("/Script/Engine.Material'/Game/3_SM/M_Green.M_Green'"));
	if (tmpMat1.Succeeded())
	{
		PloppableMaterial = tmpMat1.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> tmpMat2(TEXT("/Script/Engine.Material'/Game/3_SM/M_Red.M_Red'"));
	if (tmpMat2.Succeeded())
	{
		InvalidPloppableMaterial = tmpMat2.Object;
	}
}


void UCT_CreateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetOwner())
	{
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UCT_CreateComponent::OnOverlapStartBegin);
		GetOwner()->OnActorEndOverlap.AddDynamic(this, &UCT_CreateComponent::OnOverlapEndBegin);

	}

	UpdateState();
}


void UCT_CreateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCT_CreateComponent::UpdateState()
{
	AActor* ownerActor = GetOwner();

	if (ownerActor)
	{
		TArray<AActor*> OverlappingActors;
		ownerActor->GetOverlappingActors(OverlappingActors, TSubclassOf<AActor>());

		bIsPlacementValid = OverlappingActors.Num() == 0 ? true : false;

		//TArray<UActorComponent*> Comps = ownerActor->GetComponentsByClass(UStaticMeshComponent::StaticClass());
		TArray<UStaticMeshComponent*> Comps;
		ownerActor->GetComponents<UStaticMeshComponent>(Comps);

		//for (UActorComponent* Comp : Comps)
		for (UStaticMeshComponent* Component : Comps)
		{
			//UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(Comp);
			if (bIsPlacementValid)
			{
				//StaticMeshComp->SetMaterial(0, PloppableMaterial);
				Component->SetMaterial(0, PloppableMaterial);
			}
			else
			{
				//StaticMeshComp->SetMaterial(0, InvalidPloppableMaterial);
				Component->SetMaterial(0, InvalidPloppableMaterial);
			}

		}

		
	}
}

void UCT_CreateComponent::OnOverlapStartBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UpdateState();

}

void UCT_CreateComponent::OnOverlapEndBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UpdateState();

}

