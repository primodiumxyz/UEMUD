// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FL_UEM_Encode.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UFL_UEM_Encode : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UEMUD|Encoding")
	static FString EncodeNumber(int32 number);


	

	
};
