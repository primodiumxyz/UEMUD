// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_UEM_SyncComponentBase.h"
#include "UObject/Object.h"
#include "S_UEM_SyncComponentsBasedOnStream.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_SyncComponentsBasedOnStream : public US_UEM_SyncComponentBase
{
	GENERATED_BODY()

public:

	

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	UFUNCTION()
	void OnECSStreamServiceResponse(FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse  ECSServiceSubscribeToStreamLatestResponse);


};
