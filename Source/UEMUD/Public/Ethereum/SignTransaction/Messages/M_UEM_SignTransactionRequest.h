// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_SignTransactionRequest.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_SignTransactionRequest : public FCF_Message
{
	FM_UEM_SignTransactionRequest() = default;


	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Nonce = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GasPrice = "";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GasLimit = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ToAddress = "";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Value = "";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Data = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ChainId = "";
	
	FM_UEM_SignTransactionRequest(const FString& Nonce, const FString& GasPrice, const FString& GasLimit,
		const FString& ToAddress, const FString& Value, const FString& Data, const FString& ChainId)
		: Nonce(Nonce),
		  GasPrice(GasPrice),
		  GasLimit(GasLimit),
		  ToAddress(ToAddress),
		  Value(Value),
		  Data(Data),
		  ChainId(ChainId)
	{
	}
	
	
	
};
