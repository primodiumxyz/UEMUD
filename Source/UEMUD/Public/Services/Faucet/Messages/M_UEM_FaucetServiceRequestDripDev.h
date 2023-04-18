// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventSystem/Message/CF_Message.h"
#include "UObject/Object.h"
#include "M_UEM_FaucetServiceRequestDripDev.generated.h"



USTRUCT(BlueprintType)
struct UEMUD_API FM_UEM_FaucetServiceRequestDripDev : public FCF_Message
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FString WalletAddress;


	FM_UEM_FaucetServiceRequestDripDev()
	{
		WalletAddress = "0x";
	}
	
	FM_UEM_FaucetServiceRequestDripDev(FString _WalletAddress)
	{
		WalletAddress = _WalletAddress;
	}

	
};
