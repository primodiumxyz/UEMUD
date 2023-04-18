// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "S_UEM_SyncComponentBase.h"
#include "UObject/Object.h"
#include "S_UEM_SyncComponentsBasedOnStateSnapshotService.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_SyncComponentsBasedOnStateSnapshotService : public US_UEM_SyncComponentBase
{
	GENERATED_BODY()



	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	


	UFUNCTION()
	void OnECSStateSnapshotServiceResponse(FM_UEM_OnECSStateSnapshotService_GetStateLatestStreamResponse  GetStateLatestStreamResponse);

	
};
