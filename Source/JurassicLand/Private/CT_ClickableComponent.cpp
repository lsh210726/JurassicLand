// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_ClickableComponent.h"
#include "Components/StaticMeshComponent.h"


UCT_ClickableComponent::UCT_ClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


	ConstructorHelpers::FObjectFinder<UMaterialInterface> tmpMat1(TEXT("/Script/Engine.Material'/Game/3_SM/M_Green.M_Green'"));
	if (tmpMat1.Succeeded())
	{
		GreenMaterial = tmpMat1.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> tmpMat2(TEXT("/Script/Engine.Material'/Game/3_SM/M_Red.M_Red'"));
	if (tmpMat2.Succeeded())
	{
		RedMaterial = tmpMat2.Object;
	}

}


void UCT_ClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		GetOwner()->OnClicked.AddDynamic(this, &UCT_ClickableComponent::OnMouseClicked);

		if (IsValid(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass())))
		{
			MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		}

	}
}


void UCT_ClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCT_ClickableComponent::OnMouseClicked(AActor* ClickComponent, FKey ButtonPressed)
{
	bIsClicked = !bIsClicked;
	if(IsValid(MeshComp))
	{
		if (bIsClicked)
		{
			MeshComp->SetMaterial(0, GreenMaterial);
		}
		else
		{
			MeshComp->SetMaterial(0, RedMaterial);
		}
	}
}

void UCT_ClickableComponent::InPlacementMode()
{
	this->DestroyComponent();
}

