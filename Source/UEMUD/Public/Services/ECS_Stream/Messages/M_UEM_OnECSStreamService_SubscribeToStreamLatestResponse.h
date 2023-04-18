// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "SEcsstream/EcsStreamService.h"
#include "TurboLinkGrpc/Public/TurboLinkGrpcClient.h"
#include "M_UEM_OnECSStreamService_SubscribeToStreamLatestResponse.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FGrpcContextHandle Handle = FGrpcContextHandle();

	UPROPERTY(BlueprintReadOnly)
	FGrpcResult Result;

	UPROPERTY(BlueprintReadOnly)
	FGrpcEcsstreamECSStreamBlockBundleReply Response;

	


	FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse(
		FGrpcContextHandle _Handle,
		const FGrpcResult& _Result,
		const FGrpcEcsstreamECSStreamBlockBundleReply& _Response)
	{
		Handle = _Handle;
		Result = _Result;
		Response = _Response;
		
	}
	
	FM_UEM_OnECSStreamService_SubscribeToStreamLatestResponse()
	{
		Handle = FGrpcContextHandle();
		Result = FGrpcResult();
		Response = FGrpcEcsstreamECSStreamBlockBundleReply();
	}

	
};
