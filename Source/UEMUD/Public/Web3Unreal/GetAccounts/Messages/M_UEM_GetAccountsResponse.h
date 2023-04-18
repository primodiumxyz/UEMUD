// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ethereum/Base/Messages/M_UEM_RPCResponse.h"
#include "UObject/Object.h"
#include "M_UEM_GetAccountsResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_GetAccountsResponse : public FM_UEM_RPCResponse
{
	FM_UEM_GetAccountsResponse() = default;

	explicit FM_UEM_GetAccountsResponse(const FString& AccountAddress)
		: AccountAddress(AccountAddress)
	{
	}

	FM_UEM_GetAccountsResponse(const bool _bSuccess, const int32 _StatusCode, const FString& _Response,
		const FString& AccountAddress)
		: FM_UEM_RPCResponse(_bSuccess, _StatusCode, _Response),
		  AccountAddress(AccountAddress)
	{
	}

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FString AccountAddress = "";
    
    
};