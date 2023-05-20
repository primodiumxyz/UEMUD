// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "UObject/Object.h"
#include "EventSystem\Message\CF_Message.h"
#include "SMode/ModeMessage.h"
#include "M_UEM_OnModeService_StreamStateResponse.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnModeService_StreamStateResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FGrpcContextHandle Handle = FGrpcContextHandle();

	UPROPERTY(BlueprintReadOnly)
	FGrpcResult Result;

	UPROPERTY(BlueprintReadOnly)
	FGrpcModeQueryLayerStateStreamResponse Response;

	


	FM_UEM_OnModeService_StreamStateResponse(
		FGrpcContextHandle _Handle,
		const FGrpcResult& _Result,
		const FGrpcModeQueryLayerStateStreamResponse& _Response)
	{
		Handle = _Handle;
		Result = _Result;
		Response = _Response;
		
	}
	
	FM_UEM_OnModeService_StreamStateResponse()
	{
		Handle = FGrpcContextHandle();
		Result = FGrpcResult();
		Response = FGrpcModeQueryLayerStateStreamResponse();
	}

	
};
