// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "C_UEM_ModeServiceClient.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ModeServiceClient : public FCF_Component
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	UQueryLayerClient* QueryLayerServiceClient;

	
	FC_UEM_ModeServiceClient()
	{
		QueryLayerServiceClient = nullptr;
	}

	FC_UEM_ModeServiceClient(UQueryLayerClient* _QueryLayerServiceClient)
	{
		QueryLayerServiceClient = _QueryLayerServiceClient;
	}

	
};