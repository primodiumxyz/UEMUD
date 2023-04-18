// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_SendRawTransactionRequest.generated.h"

USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SendRawTransactionRequest : public FCF_Message
{
	GENERATED_BODY()

public:


	UPROPERTY(BlueprintReadOnly)
	FString To = "";

	UPROPERTY(BlueprintReadOnly)
	FString SignedTransaction = "";

	FM_UEM_SendRawTransactionRequest()
	{
		To = "";
		SignedTransaction = "";
	}

	FM_UEM_SendRawTransactionRequest(FString _To,FString _SignedTransaction)
	{
		To = _To;
		SignedTransaction = _SignedTransaction;
	}
	
};
