// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "D_UEM_ExecuteSystemCallInstance.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FD_UEM_ExecuteSystemCallInstance : public FCF_Component
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString ContractAbi;
	
	UPROPERTY(BlueprintReadOnly)
	FString FunctionName;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Arguments;
	

	UPROPERTY(BlueprintReadOnly)
	FString ContractAddress;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentBalance;


	UPROPERTY(BlueprintReadOnly)
	FString EncodedData;

	UPROPERTY(BlueprintReadOnly)
	int32 TransactionCount;
	UPROPERTY(BlueprintReadOnly)
	FString TransactionCountHex;

	UPROPERTY(BlueprintReadOnly)
	int32 GasPrice;
	UPROPERTY(BlueprintReadOnly)
	FString GasPriceHex;

	UPROPERTY(BlueprintReadOnly)
	int32 EstimatedGas;
	UPROPERTY(BlueprintReadOnly)
	FString EstimatedGasHex;
	
	UPROPERTY(BlueprintReadOnly)
	FString SignedTransaction;


};
