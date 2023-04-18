// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "SEcsstream/EcsStreamMessage.h"
#include "UObject/Object.h"
#include "M_UEM_ECSStream_RequestSubscribeToWorldStream.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_ECSStream_RequestSubscribeToWorldStream : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FGrpcEcsstreamECSStreamBlockBundleRequest EcsstreamECSStreamBlockBundleRequest; 


	FM_UEM_ECSStream_RequestSubscribeToWorldStream()
	{
		EcsstreamECSStreamBlockBundleRequest =FGrpcEcsstreamECSStreamBlockBundleRequest(); 
	}
	
	FM_UEM_ECSStream_RequestSubscribeToWorldStream(FGrpcEcsstreamECSStreamBlockBundleRequest _EcsstreamECSStreamBlockBundleRequest)
	{
		EcsstreamECSStreamBlockBundleRequest =_EcsstreamECSStreamBlockBundleRequest;
	}

	
};
