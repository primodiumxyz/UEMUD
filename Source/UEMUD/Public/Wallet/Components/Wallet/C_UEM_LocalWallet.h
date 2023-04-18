// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "C_UEM_LocalWallet.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_LocalWallet : public FCF_Component
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> WalletPrivateKey;

	

	
	FC_UEM_LocalWallet()
	{
		WalletPrivateKey = TArray<uint8>();
	}


	
	FC_UEM_LocalWallet(TArray<uint8> _WalletPrivateKey)
	{
		WalletPrivateKey = _WalletPrivateKey;
	}
};