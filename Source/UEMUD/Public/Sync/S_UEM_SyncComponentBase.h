// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "S_UEM_SyncComponentBase.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API US_UEM_SyncComponentBase : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	
public:

	

	UFUNCTION()
	int32 GetContextIdForEntityId(FString EntityId) const;

	UFUNCTION()
	void SynComponent(int32 ContextId, FString ComponentId, TArray<uint8> Value ) const;
	
};
