// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_EstimateGasRequest.generated.h"

USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_EstimateGasRequest : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FString FromAddress = "0x";

	UPROPERTY(BlueprintReadOnly)
	FString ToAddress= "0x";

	UPROPERTY(BlueprintReadOnly)
	FString EncodedData= "0x";

	FM_UEM_EstimateGasRequest()
	{
		FromAddress = "0x";
		ToAddress = "0x";
		EncodedData = "0x";
	}

	FM_UEM_EstimateGasRequest(FString _FromAddress, FString _ToAddress, FString _EncodedData)
	{
		FromAddress = _FromAddress;
		ToAddress = _ToAddress;
		EncodedData = _EncodedData;
	}
	
	
};
