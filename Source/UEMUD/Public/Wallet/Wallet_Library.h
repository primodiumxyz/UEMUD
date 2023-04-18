// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WalletSave.h"
#include "UObject/Object.h"
#include "Wallet_Library.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UWallet_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static TArray<uint8> CreateWallet(FString WalletName = "DefaultWallet");

	UFUNCTION(BlueprintCallable)
	static bool WalletExists(FString WalletName= "DefaultWallet");

	UFUNCTION(BlueprintCallable)
	static UWalletSave* GetWallet(FString WalletName= "DefaultWallet");

	UFUNCTION(BlueprintCallable)
	static TArray<uint8> ReadWallet(FString WalletName= "DefaultWallet");

	UFUNCTION(BlueprintCallable)
	static void SaveWalletAs(TArray<uint8> PrivateKey,FString WalletName= "DefaultWallet");
	
};




