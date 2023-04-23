// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "Contract/Systems/SED_UEM_Base.h"
#include "UObject/Object.h"
#include "C_UEM_MudSystemEncoderDecoders.generated.h"

USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_MudSystemEncoderDecoders : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	TMap<FString,USED_UEM_Base*> SystemIdToEncoderDecoder = TMap<FString,USED_UEM_Base*>();
	

	FC_UEM_MudSystemEncoderDecoders()
	{
		SystemIdToEncoderDecoder = TMap<FString,USED_UEM_Base*>();
	}


	FC_UEM_MudSystemEncoderDecoders(TMap<FString,USED_UEM_Base*> _SystemIdToEncoderDecoder)
	{
		SystemIdToEncoderDecoder = TMap<FString,USED_UEM_Base*>(_SystemIdToEncoderDecoder);
	}
};
