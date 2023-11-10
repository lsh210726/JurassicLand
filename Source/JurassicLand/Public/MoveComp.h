// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "MoveComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JURASSICLAND_API UMoveComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*Enhanced Input Comp*/
 	 void SetupPlayerEnhancedInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputActions);
	 
	 class ABasePlayer* player;

	 /* Enhanced Input - InputAction Bind Functions */
	  //Move
	  UFUNCTION()
	  void PlayerMove(const FInputActionValue& Val);
	  
	  //Look
	  UFUNCTION()
	  void PlayerLook(const FInputActionValue& Val);
		
};
