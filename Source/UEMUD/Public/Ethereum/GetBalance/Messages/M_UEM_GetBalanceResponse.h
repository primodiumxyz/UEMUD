// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ethereum/Base/Messages/M_UEM_RPCResponse.h"
#include "UObject/Object.h"
#include "M_UEM_GetBalanceResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_GetBalanceResponse : public FM_UEM_RPCResponse
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	int32 Balance; 
			 
	
	FM_UEM_GetBalanceResponse()
	{
		bSuccess = false;
		Response = "";
		StatusCode = -1;
		Balance = -1;
	}
	
	

	FM_UEM_GetBalanceResponse(const bool _bSuccess ,
		const int32 _StatusCode = -1,
		const FString _Response = "",
		int32 _Balance = -1)
	{
		bSuccess = _bSuccess;
		StatusCode = _StatusCode;
		Response = _Response;
		Balance = _Balance;
	}

	
};
