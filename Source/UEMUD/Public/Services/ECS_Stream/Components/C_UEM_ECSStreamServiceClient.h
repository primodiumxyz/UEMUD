// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "SEcsstream/EcsStreamClient.h"
#include "UObject/Object.h"
#include "C_UEM_ECSStreamServiceClient.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ECSStreamServiceClient : public FCF_Component
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	UECSStreamServiceClient* ECSStreamServiceClient;

	
	FC_UEM_ECSStreamServiceClient()
	{
		ECSStreamServiceClient = nullptr;
	}

	FC_UEM_ECSStreamServiceClient(UECSStreamServiceClient* _ECSStreamServiceClient)
	{
		ECSStreamServiceClient = _ECSStreamServiceClient;
	}

	
};