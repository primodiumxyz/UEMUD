// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_SendContractRequest.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SendContractRequest : public FCF_Message
{
	FM_UEM_SendContractRequest() = default;

	FM_UEM_SendContractRequest(const FString& ContractAddress, const FString& FunctionName, const FString& Abi,
	                           const TArray<FString>& Params, const int32 GasLimit, const FString& ValueInWei)
		: ContractAddress(ContractAddress),
		  FunctionName(FunctionName),
		  ABI(Abi),
		  Params(Params),
		  GasLimit(GasLimit),
		  ValueInWei(ValueInWei)
	{
	}


	GENERATED_BODY()




public:


	UPROPERTY(BlueprintReadOnly)
	FString ContractAddress = "";

	UPROPERTY(BlueprintReadOnly)
	FString FunctionName = "";

	UPROPERTY(BlueprintReadOnly)
	FString ABI = "";

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Params = TArray<FString>();

	UPROPERTY(BlueprintReadOnly)
	int32 GasLimit = -1;

	UPROPERTY(BlueprintReadOnly)
	FString ValueInWei = "0";


	
};
