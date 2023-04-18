// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "Components/CED_UEM_ComponentBase.h"
#include "C_UEM_MudComponentEncoderDecoders.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_MudComponentEncoderDecoders : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TMap<FString,UCED_UEM_ComponentBase*> ComponentIdToEncoderDecoder = TMap<FString,UCED_UEM_ComponentBase*>();
	

	FC_UEM_MudComponentEncoderDecoders()
	{
		ComponentIdToEncoderDecoder = TMap<FString,UCED_UEM_ComponentBase*>();
	}


	FC_UEM_MudComponentEncoderDecoders(TMap<FString,UCED_UEM_ComponentBase*> _ComponentIdToEncoderDecoder)
	{
		ComponentIdToEncoderDecoder = TMap<FString,UCED_UEM_ComponentBase*>(_ComponentIdToEncoderDecoder);
	}
};
