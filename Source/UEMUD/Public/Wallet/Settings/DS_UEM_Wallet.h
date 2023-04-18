// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DS_UEM_Wallet.generated.h"

UENUM(BlueprintType)
enum class EWalletMode : uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Local = 1 UMETA(DisplayName = "Local"),
	HyperPlay = 2  UMETA(DisplayName = "HyperPlay"),
	
};



UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Wallet Settings")) // Give it a better looking name in UI
class UEMUD_API UDS_UEM_Wallet : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config,BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EWalletMode> WalletMode = EWalletMode::HyperPlay;
	

	UPROPERTY(Config,BlueprintReadWrite, EditAnywhere)
	FString DefaultWalletName = "DefaultWallet";
	
};