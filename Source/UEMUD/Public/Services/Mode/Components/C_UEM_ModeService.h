// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core\Component\CF_Component.h"
#include "SMode/ModeService.h"
#include "C_UEM_ModeService.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ModeService : public FCF_Component
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly)
	UQueryLayer* QueryLayerService;
	


	FC_UEM_ModeService()
	{
		QueryLayerService = nullptr;
	}

	FC_UEM_ModeService(UQueryLayer* _QueryLayerService)
	{
		QueryLayerService = _QueryLayerService;
	}
	
};
