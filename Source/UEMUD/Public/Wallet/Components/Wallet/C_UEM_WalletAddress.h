// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_WalletAddress.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_WalletAddress : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FString EthWalletAddress;

	FC_UEM_WalletAddress()
	{
		EthWalletAddress = "0x";
	}


	FC_UEM_WalletAddress(FString _EthWalletAddress)
	{
		EthWalletAddress = _EthWalletAddress;
	}
	
};
