// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DS_UEM_ChainMetadata.generated.h"



UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Web3 Unreal Chain Metadata")) // Give it a better looking name in UI
class UEMUD_API UDS_UEM_ChainMetadata : public UDeveloperSettings
{

	
public:
	GENERATED_BODY()

	
	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString ChainId;
	
	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString ChainName;

	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString NativeCurrencyName;

	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	FString NativeCurrencySymbol;


	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	int32 NativeCurrencyDigits;
	
	UPROPERTY(Config,EditDefaultsOnly,BlueprintReadOnly)
	TArray<FString> RpcUrls;
	
	
};
