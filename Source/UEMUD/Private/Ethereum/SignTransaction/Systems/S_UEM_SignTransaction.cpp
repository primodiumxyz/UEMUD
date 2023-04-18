// Fill out your copyright notice in the Description page of Project Settings.


#include "Ethereum/SignTransaction/Systems/S_UEM_SignTransaction.h"

#include "Web3Utils.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Ethereum/SignTransaction/Messages/M_UEM_SignTransactionRequest.h"
#include "Ethereum/SignTransaction/Messages/M_UEM_SignTransactionResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_LocalWallet.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_SignTransaction::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_SignTransactionRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_SignTransactionRequest SignTransactionRequest)
	{
		OnSignTransactionRequest(SignTransactionRequest);
	});
	
}

void US_UEM_SignTransaction::OnSignTransactionRequest(FM_UEM_SignTransactionRequest SignTransactionRequest) const
{

	
	
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	const FC_UEM_LocalWallet LocalWallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_LocalWallet>(this);

	throw;
	//todo needs other implementations to work RLP encoding, ABI based encoding of function name and argument types
}

void US_UEM_SignTransaction::OnSignTransactionResponse(const bool bSuccess,
	FString ErrorMessage,
	FString SignedTransaction,
	FString MessageHash,
	FString TransactionHash) const 
{
	UCF_EventStatics::FireEvent_Template<FM_UEM_SignTransactionResponse>(this,
		FM_UEM_SignTransactionResponse(bSuccess,ErrorMessage,SignedTransaction,MessageHash,TransactionHash));
}