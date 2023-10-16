// Fill out your copyright notice in the Description page of Project Settings.


#include "CT_ClickableComponent.h"

UCT_ClickableComponent::UCT_ClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//OnClicked.AddDynamic(this, &UCT_ClickableComponent::OnMouseClicked);

}


void UCT_ClickableComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCT_ClickableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCT_ClickableComponent::OnMouseClicked()
{

}

