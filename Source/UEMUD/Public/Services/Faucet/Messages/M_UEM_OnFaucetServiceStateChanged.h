// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/Messages/M_UEM_OnGrpcServiceStateChanged.h"
#include "UObject/Object.h"
#include "M_UEM_OnFaucetServiceStateChanged.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_OnFaucetServiceStateChanged : public FM_UEM_OnGrpcServiceStateChanged
{
	GENERATED_BODY()

public:


	FM_UEM_OnFaucetServiceStateChanged()
	{
		NewState = EGrpcServiceState::NotCreate;
	}
	
	FM_UEM_OnFaucetServiceStateChanged(EGrpcServiceState _NewState)
	{
		NewState = _NewState;
	}

	
};
