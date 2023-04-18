// Fill out your copyright notice in the Description page of Project Settings.


#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"

#include "Core/StaticFunctionLibrary/CF_Statics.h"
#include "Endpoints/RpcCall.h"
#include "Endpoints/SendContract.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"

URpcCall* UFL_UEM_Web3EthereumRpcCalls::GetBalanceRpcCall(const UObject* WorldContextObject,
                                                          const FString& AccountAddress, int32 chainId, FString chainMetadata, FString url)
{
	const FString Params = FString::Printf(
			TEXT("\"%s\",\"latest\""),
			*AccountAddress);
	const FString Request = FString::Printf(
	TEXT("{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[%s],\"id\":\"\"}"),
	*Params);
	return URpcCall::RpcCall(WorldContextObject,Request,chainId,chainMetadata,url);
}

URpcCall* UFL_UEM_Web3EthereumRpcCalls::GetTransactionCountRpcCall(const UObject* WorldContextObject,
	const FString& AccountAddress, int32 chainId, FString chainMetadata, FString url)
{
	const FString Params = FString::Printf(
			TEXT("\"%s\",\"latest\""),
			*AccountAddress);
	const FString Request = FString::Printf(
	TEXT("{\"jsonrpc\":\"2.0\",\"method\":\"eth_getTransactionCount\",\"params\":[%s],\"id\":\"\"}"),
	*Params);
	return URpcCall::RpcCall(WorldContextObject,Request,chainId,chainMetadata,url);
}

URpcCall* UFL_UEM_Web3EthereumRpcCalls::GetGasPriceRpcCall(const UObject* WorldContextObject, int32 chainId,
	FString chainMetadata, FString url)
{
	const FString Request = FString::Printf(
	TEXT("{\"jsonrpc\":\"2.0\",\"method\":\"eth_gasPrice\",\"params\":[],\"id\":\"\"}"));
	return URpcCall::RpcCall(WorldContextObject,Request,chainId,chainMetadata,url);
}

URpcCall* UFL_UEM_Web3EthereumRpcCalls::EstimateGasRpcCall(const UObject* WorldContextObject, FString FromAddress,
	FString ToAddress, FString EncodedData, int32 chainId, FString chainMetadata, FString url)
{
	const FString Params =FString::Printf(
			TEXT("{\"from\":\"%s\",\"to\":\"%s\",\"data\":\"%s\"}"),
			*FromAddress,
			*ToAddress,
			*EncodedData);
	const FString Request = FString::Printf(
	TEXT("{\"jsonrpc\":\"2.0\",\"method\":\"eth_estimateGas\",\"params\":[%s],\"id\":\"\"}"),
	*Params);
	return URpcCall::RpcCall(WorldContextObject,Request,chainId,chainMetadata,url);
}


URpcCall* UFL_UEM_Web3EthereumRpcCalls::SignTransactionRpcCall(const UObject* WorldContextObject, FString FromAddress,
                                                               FString ToAddress, FString EncodedData, int32 chainId, FString chainMetadata, FString url)
{
	//todo to allow for local wallet
	
	FC_UEM_WalletAddress Wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(WorldContextObject);
	
	return nullptr;
	
}

URpcCall* UFL_UEM_Web3EthereumRpcCalls::SendRawTransactionRpcCall(const UObject* WorldContextObject,
	FString FromAddress, FString ToAddress, FString SignedTransaction, int32 chainId, FString chainMetadata,
	FString url)
{
	const FString Params =FString::Printf(
			TEXT("{\"from\":\"%s\",\"to\":\"%s\",\"data\":\"%s\"}"),
			*FromAddress,
			*ToAddress,
			*SignedTransaction);
	const FString Request = FString::Printf(
	TEXT("{\"jsonrpc\":\"2.0\",\"method\":\"eth_sendRawTransaction\",\"params\":[%s],\"id\":\"\"}"),
	*Params);
	return URpcCall::RpcCall(WorldContextObject,Request,chainId,chainMetadata,url);
}
