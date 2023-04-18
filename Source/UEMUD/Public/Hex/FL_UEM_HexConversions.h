// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FL_UEM_HexConversions.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UFL_UEM_HexConversions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:


	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UEM|HexConversions")
	static int32 GetNumberFromHexString(FString HexString);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UEM|HexConversions")
	static int32 GetNumberFromBytes(const TArray<uint8>& Bytes);
};
