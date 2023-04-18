// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurboLinkGrpcClient.h"
#include "SEcsstream/EcsStreamService.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_ECSStreamService.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ECSStreamService : public FCF_Component
{
	GENERATED_BODY()
public:

		

	
	UPROPERTY(BlueprintReadOnly)
	UECSStreamService* ECSStreamService;
	


	FC_UEM_ECSStreamService()
	{
		ECSStreamService = nullptr;
	}

	FC_UEM_ECSStreamService(UECSStreamService* _ECSStreamService)
	{
		ECSStreamService = _ECSStreamService;
	}

	
	
};
