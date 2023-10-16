// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CT_CreateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JURASSICLAND_API UCT_CreateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCT_CreateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	bool bIsPlacementValid = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class UMaterialInterface* PloppableMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class UMaterialInterface* InvalidPloppableMaterial;

	
public:
	
	void UpdateState();

	UFUNCTION()
	void OnOverlapStartBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEndBegin(AActor* OverlappedActor, AActor* OtherActor);
	//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		
};
