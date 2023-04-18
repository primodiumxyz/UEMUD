// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "EventSystem/Message/CF_Message.h"
#include "SFaucet/FaucetMessage.h"
#include "UObject/Object.h"
#include "M_UEM_FaucetServiceDripDevResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_FaucetServiceDripDevResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FGrpcContextHandle Handle;

	UPROPERTY(BlueprintReadOnly)
	FGrpcResult Result;
	
	UPROPERTY(BlueprintReadOnly)
	FGrpcFaucetDripResponse Response;


	FM_UEM_FaucetServiceDripDevResponse()
	{
		Handle = FGrpcContextHandle();
		Result = FGrpcResult();
		Response = FGrpcFaucetDripResponse() ;
	}
	
	FM_UEM_FaucetServiceDripDevResponse(FGrpcContextHandle _Handle,FGrpcResult _Result,FGrpcFaucetDripResponse _Response)
	{
		Handle = _Handle;
		Result = _Result;
		Response = _Response;
	}

	
};
