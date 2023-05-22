// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "UEMUD/Public/Contract/Components/DA_UEM_ComponentMappings.h"
#include "C_UEM_WorldSettings.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_WorldSettings : public FCF_Component 
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Namespace;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString WorldContractAddress;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString WorldContractAbi;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString JsonRPCUrl;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString ChainId;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UDA_UEM_ComponentMappings* ComponentMappings;
	
	


	FC_UEM_WorldSettings()
	{
		Namespace = "";
		WorldContractAddress = "0x";
		WorldContractAbi = "";
		JsonRPCUrl = "";
		ChainId = "";
		ComponentMappings = nullptr;
	}


	FC_UEM_WorldSettings(FString _Namespace,
		FString _WorldContractAddress,
		FString _WorldContractAbi,
		FString _JsonRPCUrl,
		FString _ChainId,
		UDA_UEM_ComponentMappings* _ComponentMappings)
	{
		Namespace = _Namespace;
		WorldContractAddress = _WorldContractAddress;
		WorldContractAbi = _WorldContractAbi;
		JsonRPCUrl = _JsonRPCUrl;
		ChainId = _ChainId;
		ComponentMappings = _ComponentMappings;
	}
	
};
