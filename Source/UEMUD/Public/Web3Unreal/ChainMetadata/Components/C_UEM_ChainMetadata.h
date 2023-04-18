// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_ChainMetadata.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_ChainMetadata : public FCF_Component 
{
	FC_UEM_ChainMetadata() = default;


	GENERATED_BODY()

public:
	
	FC_UEM_ChainMetadata(const FString& ChainId, const FString& ChainName, const FString& NativeCurrencyName,
			const FString& NativeCurrencySymbol, const int32 NativeCurrencyDigits, const TArray<FString>& RpcUrls)
			: ChainId(ChainId),
			  ChainName(ChainName),
			  NativeCurrencyName(NativeCurrencyName),
			  NativeCurrencySymbol(NativeCurrencySymbol),
			  NativeCurrencyDigits(NativeCurrencyDigits),
			  RpcUrls(RpcUrls)
	{
		ChainMetadataJSON = FString::Printf(TEXT("{\"chainId\":\"%s\",\"chainMetadata\":{\"chainName\":\"%s\","
									  "\"nativeCurrency\":{\"name\":\"%s\",\"symbol\":\"%s\",\"decimals\":%s},\"rpcUrls\":[\"%s\"]}}"),
			*ChainId,*ChainName,*NativeCurrencyName,*NativeCurrencySymbol,*FString::FromInt(NativeCurrencyDigits),*RpcUrls[0]);
	}
	UPROPERTY(BlueprintReadOnly)
	FString ChainId = "";
	
	UPROPERTY(BlueprintReadOnly)
	FString ChainName= "";

	UPROPERTY(BlueprintReadOnly)
	FString NativeCurrencyName= "";

	UPROPERTY(BlueprintReadOnly)
	FString NativeCurrencySymbol= "";


	UPROPERTY(BlueprintReadOnly)
	int32 NativeCurrencyDigits= 18;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> RpcUrls = TArray<FString>();

	UPROPERTY(BlueprintReadOnly)
	FString ChainMetadataJSON= "";

	
};
