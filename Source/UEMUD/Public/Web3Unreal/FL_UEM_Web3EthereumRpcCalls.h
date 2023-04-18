// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FL_UEM_Web3EthereumRpcCalls.generated.h"

/**
 * 
 */
UCLASS()
class UEMUD_API UFL_UEM_Web3EthereumRpcCalls : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
		static URpcCall* GetBalanceRpcCall(
			const UObject* WorldContextObject,
			const FString& AccountAddress,
			int32 chainId = 1,
			FString chainMetadata = "",
			FString url = "http://localhost:9680/rpc");

	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
		static URpcCall* GetTransactionCountRpcCall(
			const UObject* WorldContextObject,
			const FString& AccountAddress,
			int32 chainId = 1,
			FString chainMetadata = "",
			FString url = "http://localhost:9680/rpc");

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
		static URpcCall* GetGasPriceRpcCall(
			const UObject* WorldContextObject,
			int32 chainId = 1,
			FString chainMetadata = "",
			FString url = "http://localhost:9680/rpc");

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
	static URpcCall* EstimateGasRpcCall(
		const UObject* WorldContextObject,
		FString FromAddress = "0x",
		FString ToAddress= "0x",
		FString EncodedData= "0x",
		int32 chainId = 1,
		FString chainMetadata = "",
		FString url = "http://localhost:9680/rpc");



	

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
	static URpcCall* SignTransactionRpcCall(
		const UObject* WorldContextObject,
		FString FromAddress = "0x",
		FString ToAddress= "0x",
		FString EncodedData= "0x",
		int32 chainId = 1,
		FString chainMetadata = "",
		FString url = "http://localhost:9680/rpc");


	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "web3.unreal|Ethereum")
	static URpcCall* SendRawTransactionRpcCall(
		const UObject* WorldContextObject,
		FString FromAddress = "0x",
		FString ToAddress= "0x",
		FString SignedTransaction= "0x",
		int32 chainId = 1,
		FString chainMetadata = "",
		FString url = "http://localhost:9680/rpc");


	
	
};
