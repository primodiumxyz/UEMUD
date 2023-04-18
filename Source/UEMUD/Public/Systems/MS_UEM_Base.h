// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ethereum/GetTransactionCount/Messages/M_UEM_GetTransactionCountResponse.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceResponse.h"
#include "Ethereum/GetTransactionCount/Messages/M_UEM_GetTransactionCountResponse.h"
#include "Ethereum/GasPrice/Messages/M_UEM_GasPriceResponse.h"
#include "Ethereum/EstimateGas/Messages/M_UEM_EstimateGasResponse.h"
#include "Ethereum/SignTransaction/Messages/M_UEM_SignTransactionResponse.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionResponse.h"
#include "UObject/Object.h"
#include "Data/D_UEM_ExecuteSystemCallInstance.h"
#include "Web3Unreal/GetAccounts/Messages/M_UEM_GetAccountsResponse.h"
#include "Web3Unreal/SendContract/Messages/M_UEM_SendContractResponse.h"
#include "MS_UEM_Base.generated.h"

UCLASS()
class UEMUD_API UMS_UEM_Base : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:



	TArray<FDelegateHandle> OnGetAccountsDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnGetAccountsDelegateHandlesFreeIndexes =TArray<int32>();

	int32 GetAccountsDelegateHandlesFreeIndex()
	{
		if(OnGetAccountsDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnGetAccountsDelegateHandlesFreeIndexes[0];
			OnGetAccountsDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnGetAccountsDelegateHandlesFreeIndex(int32 Index)
	{
		OnGetAccountsDelegateHandlesFreeIndexes.Add(Index);
	}


	

	TArray<FDelegateHandle> OnGetBalanceDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnGetBalanceDelegateHandlesFreeIndexes =TArray<int32>();

	int32 GetBalanceDelegateHandlesFreeIndex()
	{
		if(OnGetBalanceDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnGetBalanceDelegateHandlesFreeIndexes[0];
			OnGetBalanceDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnGetBalanceDelegateHandlesFreeIndex(int32 Index)
	{
		OnGetBalanceDelegateHandlesFreeIndexes.Add(Index);
	}



	TArray<FDelegateHandle> OnDripDevDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnDripDevDelegateHandlesFreeIndexes =TArray<int32>();

	int32 DripDevDelegateHandlesFreeIndex()
	{
		if(OnDripDevDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnDripDevDelegateHandlesFreeIndexes[0];
			OnDripDevDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnDripDevDelegateHandlesFreeIndex(int32 Index)
	{
		OnDripDevDelegateHandlesFreeIndexes.Add(Index);
	}




	TArray<FDelegateHandle> OnGetTransactionCountDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnGetTransactionCountDelegateHandlesFreeIndexes =TArray<int32>();

	int32 GetTransactionCountDelegateHandlesFreeIndex()
	{
		if(OnGetTransactionCountDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnGetTransactionCountDelegateHandlesFreeIndexes[0];
			OnGetTransactionCountDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnGetTransactionCountDelegateHandlesFreeIndex(int32 Index)
	{
		OnGetTransactionCountDelegateHandlesFreeIndexes.Add(Index);
	}




	TArray<FDelegateHandle> OnGasPriceDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnGasPriceDelegateHandlesFreeIndexes =TArray<int32>();

	int32 GasPriceDelegateHandlesFreeIndex()
	{
		if(OnGasPriceDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnGasPriceDelegateHandlesFreeIndexes[0];
			OnGasPriceDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnGasPriceDelegateHandlesFreeIndex(int32 Index)
	{
		OnGasPriceDelegateHandlesFreeIndexes.Add(Index);
	}

	TArray<FDelegateHandle> OnEstimateGasDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnEstimateGasDelegateHandlesFreeIndexes =TArray<int32>();

	int32 EstimateGasDelegateHandlesFreeIndex()
	{
		if(OnEstimateGasDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnEstimateGasDelegateHandlesFreeIndexes[0];
			OnEstimateGasDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnEstimateGasDelegateHandlesFreeIndex(int32 Index)
	{
		OnEstimateGasDelegateHandlesFreeIndexes.Add(Index);
	}
	
	
	TArray<FDelegateHandle> OnSignTransactionDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnSignTransactionDelegateHandlesFreeIndexes =TArray<int32>();

	int32 SignTransactionDelegateHandlesFreeIndex()
	{
		if(OnSignTransactionDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnSignTransactionDelegateHandlesFreeIndexes[0];
			OnSignTransactionDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnSignTransactionDelegateHandlesFreeIndex(int32 Index)
	{
		OnSignTransactionDelegateHandlesFreeIndexes.Add(Index);
	}


	TArray<FDelegateHandle> OnSendRawTransactionDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnSendRawTransactionDelegateHandlesFreeIndexes =TArray<int32>();

	int32 SendRawTransactionDelegateHandlesFreeIndex()
	{
		if(OnSendRawTransactionDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnSendRawTransactionDelegateHandlesFreeIndexes[0];
			OnSendRawTransactionDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnSendRawTransactionDelegateHandlesFreeIndex(int32 Index)
	{
		OnSendRawTransactionDelegateHandlesFreeIndexes.Add(Index);
	}


	TArray<FDelegateHandle> OnSendContractDelegateHandles = TArray<FDelegateHandle>();
	TArray<int32> OnSendContractDelegateHandlesFreeIndexes =TArray<int32>();

	int32 SendContractDelegateHandlesFreeIndex()
	{
		if(OnSendContractDelegateHandlesFreeIndexes.Num() > 0)
		{
			const int32 FreeIndex = OnSendContractDelegateHandlesFreeIndexes[0];
			OnSendContractDelegateHandlesFreeIndexes.RemoveAt(0);
			return FreeIndex;
		}
		return -1;
	}

	void ReturnSendContractDelegateHandlesFreeIndex(int32 Index)
	{
		OnSendContractDelegateHandlesFreeIndexes.Add(Index);
	}

	
public:

	
	
	


	UFUNCTION()
	virtual FString GetSystemId();

	UFUNCTION()
	virtual FString GetHexSystemId();

	

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	

	UFUNCTION()
	void ExecuteSystemCall(
		FString ContractAddress,
		const FString& ContractAbi,
		const FString& FunctionName,
		const TArray<FString> Arguments,
		const FString& EncodedArguments);


	void OnGetAccountsResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnGetBalanceDelegateHandleIndex,
		FM_UEM_GetAccountsResponse GetAccountsResponse);
	
	
	void OnGetBalanceResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnGetBalanceDelegateHandleIndex,
		FM_UEM_GetBalanceResponse GetBalanceResponse);

	void GetBalanceRetryTimerElapsed();
	
	void OnGetTransactionCountResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnGetTransactionCountDelegateHandleIndex,
		FM_UEM_GetTransactionCountResponse GetTransactionCountResponse);


	
	void OnGasPriceResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnGasPriceDelegateHandleIndex,
		FM_UEM_GasPriceResponse GetBalanceResponse);

	
	void OnEstimateGasResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnEstimateGasDelegateHandleIndex,
		FM_UEM_EstimateGasResponse EstimateGasResponse) ;


	
	void OnSignTransactionResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnSignTransactionDelegateHandleIndex,
		FM_UEM_SignTransactionResponse SignTransactionResponse) ;

	
	void OnSendRawTransactionResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnSendRawTransactionDelegateHandleIndex,
		FM_UEM_SendRawTransactionResponse SendRawTransactionResponse) ;


	void OnSendContractResponse(
		FD_UEM_ExecuteSystemCallInstance ExecuteSystemCallInstance,
		int32 OnSendContractDelegateHandleIndex,
		FM_UEM_SendContractResponse SendContractResponse) ;



	
};
