// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "UEMUD/Public/Components/DA_UEM_ComponentMappings.h"
#include "C_UEM_WorldSettings.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_WorldSettings : public FCF_Component 
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	FString WorldContractAddress;
	UPROPERTY(BlueprintReadOnly)
	FString JsonRPCUrl;
	UPROPERTY(BlueprintReadOnly)
	FString ChainId;
	
	UPROPERTY(BlueprintReadOnly)
	UDA_UEM_ComponentMappings* ComponentMappings;
	
	


	FC_UEM_WorldSettings()
	{
		WorldContractAddress = "0x";
		JsonRPCUrl = "";
		ChainId = "";
		ComponentMappings = nullptr;
	}

	FC_UEM_WorldSettings(FString _WorldContractAddress,
		FString _JsonRPCUrl,
		FString _ChainId,
		UDA_UEM_ComponentMappings* _ComponentMappings)
	{
		WorldContractAddress = _WorldContractAddress;
		JsonRPCUrl = _JsonRPCUrl;
		ChainId = _ChainId;
		ComponentMappings = _ComponentMappings;
	}
	
};
