// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "Contract/ContractEncoderDecoder_UEM_Base.h"
#include "UObject/Object.h"
#include "SED_UEM_Base.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UEMUD_API USED_UEM_Base : public UContractEncoderDecoder_UEM_Base
{
	GENERATED_BODY()

public:




	UFUNCTION()
	virtual const FString GetEncodedArguments(FInstancedStruct SystemArgumentsStruct);

	UFUNCTION()
	virtual const TArray<FString> GetStringArguments(FInstancedStruct SystemArgumentsStruct);

	UFUNCTION()
	virtual const FString GetFunctionToExecute();

	UFUNCTION()
	virtual const FString GetEncodedFunctionToExecute();
	
};
