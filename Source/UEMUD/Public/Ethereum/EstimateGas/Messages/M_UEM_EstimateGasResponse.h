// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Ethereum/Base/Messages/M_UEM_RPCResponse.h"
#include "UObject/Object.h"
#include "M_UEM_EstimateGasResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_EstimateGasResponse : public FM_UEM_RPCResponse
{
	GENERATED_BODY()

public:


	UPROPERTY(BlueprintReadOnly)
	int32 EstimatedGas; 
			 
	
	FM_UEM_EstimateGasResponse()
	{
		bSuccess = false;
		Response = "";
		StatusCode = -1;
		EstimatedGas = -1;
	}
	
	

	FM_UEM_EstimateGasResponse(const bool _bSuccess ,
		const int32 _StatusCode = -1,
		const FString _Response = "",
		int32 _EstimatedGas = -1)
	{
		bSuccess = _bSuccess;
		StatusCode = _StatusCode;
		Response = _Response;
		EstimatedGas = _EstimatedGas;
	}
	
};
