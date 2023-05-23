// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FL_ST_Sync.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UFL_ST_Sync : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static int32 GetContextIdForEntityId(UObject* WorldContextObject,FString entityId);

	UFUNCTION(BlueprintCallable)
	static FString GetEntityIdForContextId(UObject* WorldContextObject,int32 contextId);

	UFUNCTION(BlueprintCallable)
	static bool EntityIdExistsForContextId(UObject* WorldContextObject,int32 contextId);
	
};
