// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EventSystem\Message\CF_Message.h"
#include "Services/Messages/M_UEM_OnGrpcServiceStateChanged.h"
#include "M_UEM_OnModeService_StateChanged.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnModeService_StateChanged : public FM_UEM_OnGrpcServiceStateChanged
{
	GENERATED_BODY()

public:


	FM_UEM_OnModeService_StateChanged()
	{
		NewState = EGrpcServiceState::NotCreate;
	}
	
	FM_UEM_OnModeService_StateChanged(EGrpcServiceState _NewState)
	{
		NewState = _NewState;
	}

	
};