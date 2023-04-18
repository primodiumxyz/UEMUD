// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_SignTransactionResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SignTransactionResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bSuccess = false;
	UPROPERTY(BlueprintReadOnly)
	FString ErrorMessage = "";

	UPROPERTY(BlueprintReadOnly)
	FString SignedTransaction;
	UPROPERTY(BlueprintReadOnly)
	FString  MessageHash;
	UPROPERTY(BlueprintReadOnly)
	FString TransactionHash;
	
	FM_UEM_SignTransactionResponse()
	{
		SignedTransaction = "";
		MessageHash = "";
		TransactionHash = "";
		ErrorMessage = "";
		bSuccess = false;
	}
	
	FM_UEM_SignTransactionResponse(
		bool _bSuccess,
		FString  _ErrorMessage,
		FString _SignedTransaction,
		FString  _MessageHash ,
		FString  _TransactionHash)
	{
		bSuccess = _bSuccess;
		ErrorMessage = _ErrorMessage;
		SignedTransaction = _SignedTransaction;
		MessageHash = _MessageHash;
		TransactionHash = _TransactionHash;
	}

	
};