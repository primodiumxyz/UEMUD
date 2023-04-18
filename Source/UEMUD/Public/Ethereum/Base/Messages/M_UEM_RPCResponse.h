// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_RPCResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_RPCResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 StatusCode = -1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Response = "";
	
	
	FM_UEM_RPCResponse()
	{
		bSuccess = false;
		StatusCode = -1;
		Response = "";
	}
	
	FM_UEM_RPCResponse(const bool _bSuccess ,
		const int32 _StatusCode = -1,
		const FString _Response = "")
	{
		bSuccess = _bSuccess;
		StatusCode = _StatusCode;
		Response = _Response;
	}

	
};
