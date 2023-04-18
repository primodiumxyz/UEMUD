// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ethereum/Base/Messages/M_UEM_RPCResponse.h"
#include "UObject/Object.h"
#include "M_UEM_SendRawTransactionResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SendRawTransactionResponse : public FM_UEM_RPCResponse
{


	FM_UEM_SendRawTransactionResponse() :FM_UEM_RPCResponse(),TransactionHash("0x") 
	{
		
	}
	
	explicit FM_UEM_SendRawTransactionResponse(const FString& TransactionHash)
		: TransactionHash(TransactionHash)
	{
	}

	FM_UEM_SendRawTransactionResponse(const bool _bSuccess, const int32 _StatusCode, const FString& _Response,
		const FString& TransactionHash)
		: FM_UEM_RPCResponse(_bSuccess, _StatusCode, _Response),
		  TransactionHash(TransactionHash)
	{
	}

	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	FString TransactionHash = ""; 
	
	
};