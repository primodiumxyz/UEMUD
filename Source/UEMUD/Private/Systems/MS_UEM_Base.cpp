// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/MS_UEM_Base.h"

#include <string>

#include "Keccak256.h"
#include "Keccak256Helper.h"
#include "Ethereum/EstimateGas/Messages/M_UEM_EstimateGasRequest.h"
#include "Ethereum/EstimateGas/Messages/M_UEM_EstimateGasResponse.h"
#include "Ethereum/GasPrice/Messages/M_UEM_GasPriceRequest.h"
#include "Ethereum/GasPrice/Messages/M_UEM_GasPriceResponse.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceRequest.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceResponse.h"
#include "Ethereum/GetTransactionCount/Messages/M_UEM_GetTransactionCountRequest.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionRequest.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionResponse.h"
#include "Ethereum/SignTransaction/Messages/M_UEM_SignTransactionResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Services/Faucet/Messages/M_UEM_FaucetServiceDripDevResponse.h"
#include "Services/Faucet/Messages/M_UEM_FaucetServiceRequestDripDev.h"
#include "Systems/Data/D_UEM_ExecuteSystemCallInstance.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsRequest.h"
#include "Web3Unreal/SendContract/Messages/M_UEM_SendContractRequest.h"
#include "Web3Unreal/SendContract/Messages/M_UEM_SendContractResponse.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"

FString UMS_UEM_Base::GetSystemId()
{
	throw;
}

FString UMS_UEM_Base::GetHexSystemId()
{
	return UKeccak256Helper::Keccak256(GetSystemId());
}

bool UMS_UEM_Base::ShouldCreateSubsystem(UObject* Outer) const
{
	return false;
}

void UMS_UEM_Base::ExecuteSystemCall(FString ContractAddress,const FString& ContractAbi, const FString& FunctionName,
                                     const TArray<FString> Arguments, const FString& EncodedArguments)
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);

	FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance = FD_UEM_ExecuteSystemCallInstance();
	ExecuteSystemCallInstance.ContractAbi = ContractAbi;
	ExecuteSystemCallInstance.ContractAddress = ContractAddress;
	ExecuteSystemCallInstance.FunctionName = FunctionName;
	ExecuteSystemCallInstance.Arguments = TArray<FString>(Arguments);
	

	int32 OnGetAccountsDelegateHandleIndex = GetAccountsDelegateHandlesFreeIndex();
	if(OnGetAccountsDelegateHandleIndex < 0)
	{
		OnGetAccountsDelegateHandleIndex = OnGetAccountsDelegateHandles.Num();
		OnGetAccountsDelegateHandles.SetNum(OnGetAccountsDelegateHandles.Num() + 1);
	}
	
	OnGetAccountsDelegateHandles[OnGetAccountsDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_GetAccountsResponse>(this,
		[this,OnGetAccountsDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_GetAccountsResponse GetAccountsResponse)
		{
			OnGetAccountsResponse(ExecuteSystemCallInstance,OnGetAccountsDelegateHandleIndex,GetAccountsResponse);
		});
	UCF_EventStatics::FireEvent_Template<FM_UEM_GetAccountsRequest>(this,FM_UEM_GetAccountsRequest());
	

	
}

void UMS_UEM_Base::OnGetAccountsResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnGetAccountsDelegateHandleIndex, FM_UEM_GetAccountsResponse GetAccountsResponse)
{
	if(!UCF_EventStatics::RemoveLambda<FM_UEM_GetAccountsResponse>(
				this,
				OnGetAccountsDelegateHandles[OnGetAccountsDelegateHandleIndex]))
					throw;

	UCF_GroupsStatics::SetSingletonComponent<FC_UEM_WalletAddress>(this,FC_UEM_WalletAddress(GetAccountsResponse.AccountAddress));

	
	
	int32 OnGetBalanceDelegateHandleIndex = GetBalanceDelegateHandlesFreeIndex();
	if(OnGetBalanceDelegateHandleIndex < 0)
	{
		OnGetBalanceDelegateHandleIndex = OnGetBalanceDelegateHandles.Num();
		OnGetBalanceDelegateHandles.SetNum(OnGetBalanceDelegateHandles.Num() + 1);
	}
	
	OnGetBalanceDelegateHandles[OnGetBalanceDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_GetBalanceResponse>(this,
		[this,OnGetBalanceDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_GetBalanceResponse GetBalanceResponse)
		{
			OnGetBalanceResponse(ExecuteSystemCallInstance,OnGetBalanceDelegateHandleIndex,GetBalanceResponse);
		});
	UCF_EventStatics::FireEvent_Template<FM_UEM_GetBalanceRequest>(this,FM_UEM_GetBalanceRequest());
	
}

void UMS_UEM_Base::OnGetBalanceResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
                                        int32 OnGetBalanceDelegateHandleIndex, FM_UEM_GetBalanceResponse GetBalanceResponse)
{

	if(!GetBalanceResponse.bSuccess )
	{
		
		UE_LOG(LogTemp, Error, TEXT("Get Balance Failed! Response Body: %s"), *GetBalanceResponse.Response);
		UCF_EventStatics::FireEvent_Template<FM_UEM_GetBalanceRequest>(this,FM_UEM_GetBalanceRequest());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Get Balance Success! Response Body: %s" ), *GetBalanceResponse.Response);
	}
	
	ExecuteSystemCallInstance.CurrentBalance = GetBalanceResponse.Balance;
	constexpr int32 MinBalance = 2000000; 
	if(ExecuteSystemCallInstance.CurrentBalance < MinBalance && false)
	{
		UE_LOG(LogTemp, Log, TEXT("Balance is Low Requesting Drip"));
		int32 OnDripDevDelegateHandleIndex = DripDevDelegateHandlesFreeIndex();
		if(OnDripDevDelegateHandleIndex < 0)
		{
			OnDripDevDelegateHandleIndex = OnDripDevDelegateHandles.Num();
			OnDripDevDelegateHandles.SetNum(OnDripDevDelegateHandles.Num() + 1);
		}
	
		OnDripDevDelegateHandles[OnDripDevDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_FaucetServiceDripDevResponse>(this,
		[this,OnDripDevDelegateHandleIndex](const UObject* Invoker,const FM_UEM_FaucetServiceDripDevResponse FaucetServiceDripDevResponse)
		{
			if(FaucetServiceDripDevResponse.Result.Code == EGrpcResultCode::Ok)
			{
				UE_LOG(LogTemp, Log, TEXT("Request Drip Success! Response Body: %s" ), *FaucetServiceDripDevResponse.Response.DripTxHash);
				UCF_EventStatics::RemoveLambda<FM_UEM_FaucetServiceDripDevResponse>(this,OnDripDevDelegateHandles[OnDripDevDelegateHandleIndex]);

				FTimerHandle UnusedHandle;
				GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(
				UnusedHandle, this, &UMS_UEM_Base::GetBalanceRetryTimerElapsed, 2, false);
				return;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Request Drip Fail! Response Body:  %s" ), *FaucetServiceDripDevResponse.Response.DripTxHash);
				UCF_EventStatics::FireEvent_Template<FM_UEM_FaucetServiceRequestDripDev>(this,FM_UEM_FaucetServiceRequestDripDev());
				return;
			}
		});
		UCF_EventStatics::FireEvent_Template<FM_UEM_FaucetServiceRequestDripDev>(this,FM_UEM_FaucetServiceRequestDripDev());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Balance is Ok Moving Forward current balance: %s , %s"), *(FString::FromInt(ExecuteSystemCallInstance.CurrentBalance)),*(FString::FromInt(MinBalance)));
		if(!UCF_EventStatics::RemoveLambda<FM_UEM_GetBalanceResponse>(
			this,
			OnGetBalanceDelegateHandles[OnGetBalanceDelegateHandleIndex]))
				throw;
				
		const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);


	

		int32 OnSendContractDelegateHandleIndex = SendContractDelegateHandlesFreeIndex();
		if(OnSendContractDelegateHandleIndex < 0)
		{
			OnSendContractDelegateHandleIndex = OnSendContractDelegateHandles.Num();
			OnSendContractDelegateHandles.SetNum(OnSendContractDelegateHandles.Num() + 1);
		}
	
		OnSendContractDelegateHandles[OnSendContractDelegateHandleIndex]  = UCF_EventStatics::AddLambdaListener<FM_UEM_SendContractResponse>(this,
			[this,OnSendContractDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_SendContractResponse SendContractResponse)
			{
				OnSendContractResponse(
					ExecuteSystemCallInstance,
					OnSendContractDelegateHandleIndex,
					SendContractResponse);
			});
	
		UCF_EventStatics::FireEvent_Template<FM_UEM_SendContractRequest>(this,
				FM_UEM_SendContractRequest(
					ExecuteSystemCallInstance.ContractAddress,
					ExecuteSystemCallInstance.FunctionName,
					ExecuteSystemCallInstance.ContractAbi,
					ExecuteSystemCallInstance.Arguments,
					-1,
					"0"));
	
	


		// int32 OnGetTransactionCountDelegateHandleIndex = GetTransactionCountDelegateHandlesFreeIndex();
		// if(OnGetTransactionCountDelegateHandleIndex < 0)
		// {
		// 	OnGetTransactionCountDelegateHandleIndex = OnGetTransactionCountDelegateHandles.Num();
		// 	OnGetTransactionCountDelegateHandles.SetNum(OnGetTransactionCountDelegateHandles.Num() + 1);
		// }
		//
		// OnGetTransactionCountDelegateHandles[OnGetTransactionCountDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_GetTransactionCountResponse>(this,
		// [this,OnGetTransactionCountDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_GetTransactionCountResponse GetTransactionCountResponse)
		// {
		// 	OnGetTransactionCountResponse(
		// 		ExecuteSystemCallInstance,
		// 		OnGetTransactionCountDelegateHandleIndex,
		// 		GetTransactionCountResponse);
		// });
		// UCF_EventStatics::FireEvent_Template<FM_UEM_GetTransactionCountRequest>(this,FM_UEM_GetTransactionCountRequest());
		// 		
	}
	
}

void UMS_UEM_Base::GetBalanceRetryTimerElapsed()
{
	UCF_EventStatics::FireEvent_Template<FM_UEM_GetBalanceRequest>(this,FM_UEM_GetBalanceRequest());
}

void UMS_UEM_Base::OnGetTransactionCountResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
                                                 int32 OnGetTransactionCountDelegateHandleIndex, FM_UEM_GetTransactionCountResponse GetTransactionCountResponse)
{
	
	if(!GetTransactionCountResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Get Transaction Count Fail! Response Body:  %s" ), *GetTransactionCountResponse.Response);
		UCF_EventStatics::FireEvent_Template<FM_UEM_GetTransactionCountRequest>(this,FM_UEM_GetTransactionCountRequest());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Get Transaction Count Success! Response Body:  %s" ), *GetTransactionCountResponse.Response);
		UCF_EventStatics::RemoveLambda<FM_UEM_GetTransactionCountResponse>(
			this,
			OnGetTransactionCountDelegateHandles[OnGetTransactionCountDelegateHandleIndex]);
	}

	
	ExecuteSystemCallInstance.TransactionCount = GetTransactionCountResponse.TransactionCount;

	int32 OnGasPriceDelegateHandleIndex = GasPriceDelegateHandlesFreeIndex();
	if(OnGasPriceDelegateHandleIndex < 0)
	{
		OnGasPriceDelegateHandleIndex = OnGasPriceDelegateHandles.Num();
		OnGasPriceDelegateHandles.SetNum(OnGasPriceDelegateHandles.Num() + 1);
	}
	
	OnGasPriceDelegateHandles[OnGasPriceDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_GasPriceResponse>(this,
		[this,OnGasPriceDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_GasPriceResponse GasPriceResponse)
		{
			OnGasPriceResponse(
				ExecuteSystemCallInstance,
				OnGasPriceDelegateHandleIndex,
				GasPriceResponse);
		});

	
	UCF_EventStatics::FireEvent_Template<FM_UEM_GasPriceRequest>(this,FM_UEM_GasPriceRequest());
			
	
}

void UMS_UEM_Base::OnGasPriceResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnGasPriceDelegateHandleIndex, FM_UEM_GasPriceResponse GasPriceResponse)
{

	if(!GasPriceResponse.bSuccess )
	{
		UE_LOG(LogTemp, Error, TEXT("Gas Price Failed! Response Body:  %s" ), *GasPriceResponse.Response);
		UCF_EventStatics::FireEvent_Template<FM_UEM_GasPriceRequest>(this,FM_UEM_GasPriceRequest());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Gas Price Sucess! Response Body:  %s" ), *GasPriceResponse.Response );
		UCF_EventStatics::RemoveLambda<FM_UEM_GasPriceResponse>(
		this,
		OnGasPriceDelegateHandles[OnGasPriceDelegateHandleIndex]);
		
	}
	ExecuteSystemCallInstance.GasPrice = GasPriceResponse.GasPrice;
	int32 OnEstimateGasDelegateHandleIndex = EstimateGasDelegateHandlesFreeIndex();
	if(OnEstimateGasDelegateHandleIndex < 0)
	{
		OnEstimateGasDelegateHandleIndex = OnEstimateGasDelegateHandles.Num();
		OnEstimateGasDelegateHandles.SetNum(OnEstimateGasDelegateHandles.Num() + 1);
	}
	
	OnEstimateGasDelegateHandles[OnEstimateGasDelegateHandleIndex]  = UCF_EventStatics::AddLambdaListener<FM_UEM_EstimateGasResponse>(this,
		[this,OnEstimateGasDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_EstimateGasResponse EstimateGasResponse)
		{
			OnEstimateGasResponse(
				ExecuteSystemCallInstance,
				OnEstimateGasDelegateHandleIndex,
				EstimateGasResponse);
		});

	
	
			
	
}

void UMS_UEM_Base::OnEstimateGasResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnEstimateGasDelegateHandleIndex, FM_UEM_EstimateGasResponse EstimateGasResponse) 
{
	if(!EstimateGasResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Estimate Gas Failed! Response Body:  %s" ), *EstimateGasResponse.Response);
		UCF_EventStatics::FireEvent_Template<FM_UEM_EstimateGasRequest>(this,FM_UEM_EstimateGasRequest());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Estimate Gas Success! Response Body:  %s" ), *EstimateGasResponse.Response );
		UCF_EventStatics::RemoveLambda<FM_UEM_EstimateGasResponse>(this,OnEstimateGasDelegateHandles[OnEstimateGasDelegateHandleIndex]);
	}
	ExecuteSystemCallInstance.EstimatedGas = EstimateGasResponse.EstimatedGas;

	int32 OnSendContractDelegateHandleIndex = SendContractDelegateHandlesFreeIndex();
	if(OnSendContractDelegateHandleIndex < 0)
	{
		OnSendContractDelegateHandleIndex = OnSendContractDelegateHandles.Num();
		OnSendContractDelegateHandles.SetNum(OnSendContractDelegateHandles.Num() + 1);
	}
	
	OnSendContractDelegateHandles[OnSendContractDelegateHandleIndex]  = UCF_EventStatics::AddLambdaListener<FM_UEM_SendContractResponse>(this,
		[this,OnSendContractDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_SendContractResponse SendContractResponse)
		{
			OnSendContractResponse(
				ExecuteSystemCallInstance,
				OnSendContractDelegateHandleIndex,
				SendContractResponse);
		});

	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	UCF_EventStatics::FireEvent_Template<FM_UEM_SendContractRequest>(this,
			FM_UEM_SendContractRequest(
				wallet.EthWalletAddress,
				ExecuteSystemCallInstance.FunctionName,
				ExecuteSystemCallInstance.ContractAbi,
				ExecuteSystemCallInstance.Arguments,
				ExecuteSystemCallInstance.EstimatedGas,
				""));
	
	
}



void UMS_UEM_Base::OnSendContractResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnSendContractDelegateHandleIndex, FM_UEM_SendContractResponse SendContractResponse)
{
	UCF_EventStatics::RemoveLambda<FM_UEM_SendContractResponse>(this,OnSendContractDelegateHandles[OnSendContractDelegateHandleIndex]);

	if(!SendContractResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Send Contract Fail: %s"),*SendContractResponse.Response);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Send Contract Success Transaction Hash: %s \n Response: %s"),*SendContractResponse.TransactionHash,*SendContractResponse.Response);
		
	}
	
}




void UMS_UEM_Base::OnSignTransactionResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnSignTransactionDelegateHandleIndex, FM_UEM_SignTransactionResponse SignTransactionResponse)
{

	if(SignTransactionResponse.bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Sign Transaction Successful! Transaction Hash:  %s" ), *SignTransactionResponse.TransactionHash );
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Sign Transaction Failed! Transaction Hash:  %s" ), *SignTransactionResponse.TransactionHash );
	}
	UCF_EventStatics::RemoveLambda<FM_UEM_SignTransactionResponse>(this,OnSignTransactionDelegateHandles[OnSignTransactionDelegateHandleIndex]);
	ExecuteSystemCallInstance.SignedTransaction = SignTransactionResponse.SignedTransaction;

	int32 OnSendRawTransactionDelegateHandleIndex = SendRawTransactionDelegateHandlesFreeIndex();
	if(OnSendRawTransactionDelegateHandleIndex < 0)
	{
		OnSendRawTransactionDelegateHandleIndex = OnSendRawTransactionDelegateHandles.Num();
		OnSendRawTransactionDelegateHandles.SetNum(OnSendRawTransactionDelegateHandles.Num() + 1);
	}
	
	OnSendRawTransactionDelegateHandles[OnSendRawTransactionDelegateHandleIndex] = UCF_EventStatics::AddLambdaListener<FM_UEM_SendRawTransactionResponse>(this,
		[this,OnSendRawTransactionDelegateHandleIndex,ExecuteSystemCallInstance](const UObject* Invoker,const FM_UEM_SendRawTransactionResponse SendRawTransactionResponse)
		{
			OnSendRawTransactionResponse(
				ExecuteSystemCallInstance,
				OnSendRawTransactionDelegateHandleIndex,
				SendRawTransactionResponse);
		});

	UCF_EventStatics::FireEvent_Template<FM_UEM_SendRawTransactionRequest>(this,
			FM_UEM_SendRawTransactionRequest(ExecuteSystemCallInstance.ContractAddress,ExecuteSystemCallInstance.SignedTransaction));
}

void UMS_UEM_Base::OnSendRawTransactionResponse(FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
	int32 OnSendRawTransactionDelegateHandleIndex, FM_UEM_SendRawTransactionResponse SendRawTransactionResponse)
{
	UCF_EventStatics::RemoveLambda<FM_UEM_SendRawTransactionResponse>(this,OnSendRawTransactionDelegateHandles[OnSendRawTransactionDelegateHandleIndex]);

	if(!SendRawTransactionResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Send Raw Transaction Fail Internal!" ));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Send Raw Transaction Success Internal!" ));
	}
	
	UE_LOG(LogTemp, Log, TEXT("System Call Successful! Transaction Hash:  %s" ), *SendRawTransactionResponse.TransactionHash );
}


