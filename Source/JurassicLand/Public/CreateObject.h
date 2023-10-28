// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreateObject.generated.h"


UENUM(BlueprintType)
enum class ECreateObject : uint8 {
	Tree,
	Rock,
	Road,
	Store,
};

UCLASS()
class JURASSICLAND_API ACreateObject : public AActor
{
	GENERATED_BODY()
public:	
	ACreateObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MySettings")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	class UCT_CreateComponent* createComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	class UCT_ClickableComponent* clickComp;

};
