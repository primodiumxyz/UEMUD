// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcService.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_OnGrpcServiceStateChanged.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnGrpcServiceStateChanged : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	EGrpcServiceState NewState;

	FM_UEM_OnGrpcServiceStateChanged()
	{
		NewState = EGrpcServiceState::NotCreate;
	}
	
	FM_UEM_OnGrpcServiceStateChanged(EGrpcServiceState _NewState)
	{
		NewState = _NewState;
	}

	
};
