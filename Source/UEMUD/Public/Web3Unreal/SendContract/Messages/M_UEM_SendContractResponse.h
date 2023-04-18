// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ethereum/Base/Messages/M_UEM_RPCResponse.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_SendContractResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SendContractResponse : public FM_UEM_RPCResponse
{
    FM_UEM_SendContractResponse() = default;

    explicit FM_UEM_SendContractResponse(const FString& TransactionHash)
        : TransactionHash(TransactionHash)
    {
    }

    FM_UEM_SendContractResponse(const bool _bSuccess, const int32 _StatusCode, const FString& _Response,
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