// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Component/CF_Component.h"
#include "UObject/Object.h"
#include "Wallet/Settings/DS_UEM_Wallet.h"
#include "C_UEM_WalletSettings.generated.h"


USTRUCT(BlueprintType)
struct UEMUD_API FC_UEM_WalletSettings : public FCF_Component
{
	GENERATED_BODY()

public:

	UPROPERTY(Config,BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EWalletMode> WalletMode = EWalletMode::HyperPlay;
	

	UPROPERTY(Config,BlueprintReadWrite, EditAnywhere)
	FString DefaultWalletName = "DefaultWallet";

	FC_UEM_WalletSettings()
	{
		WalletMode = EWalletMode::HyperPlay;
		DefaultWalletName = "DefaultWallet";
	}


	FC_UEM_WalletSettings(TEnumAsByte<EWalletMode> _WalletMode,	FString _DefaultWalletName )
	{
		WalletMode = _WalletMode;
		DefaultWalletName = _DefaultWalletName;
	}
	
};
