// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CT_ClickableComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JURASSICLAND_API UCT_ClickableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCT_ClickableComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	bool bIsClicked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class UMaterialInterface* RedMaterial;

public:

	UFUNCTION()
	void OnMouseClicked(AActor* ClickComponent, FKey ButtonPressed);

	void InPlacementMode();

		
};
