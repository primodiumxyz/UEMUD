// Fill out your copyright notice in the Description page of Project Settings.

#include "Ethereum/SendRawTransaction/Systems/S_UEM_SendRawTransaction.h"
#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/RpcCall.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionRequest.h"
#include "Ethereum/SendRawTransaction/Messages/M_UEM_SendRawTransactionResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"






void US_UEM_SendRawTransaction::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_SendRawTransactionRequest>(this,
		[this](const UObject* Invoker, FM_UEM_SendRawTransactionRequest SendRawTransactionCountRequest)
	{
		OnSendRawTransactionRequest(SendRawTransactionCountRequest);
	});
	
}

void US_UEM_SendRawTransaction::OnSendRawTransactionRequest(FM_UEM_SendRawTransactionRequest SendRawTransactionCountRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	URpcCall* RpcCall = UFL_UEM_Web3EthereumRpcCalls::SendRawTransactionRpcCall(this,
		wallet.EthWalletAddress,
		SendRawTransactionCountRequest.To,
		SendRawTransactionCountRequest.SignedTransaction,
		FCString::Atoi(*worldSettings.ChainId),
"",
			worldSettings.JsonRPCUrl);
	RpcCall->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
		if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			if(JsonObject->HasField("result"))
			{
				const FString BalanceHex = JsonObject->GetStringField("result");
				UCF_EventStatics::FireEvent_Template<FM_UEM_SendRawTransactionResponse>(this,FM_UEM_SendRawTransactionResponse(true,StatusCode,Response,BalanceHex));
			}
			else
			{
				UE_LOG(LogTemp,Error,
				TEXT("No field 'result' in response: %s"),
				*Response);
			}
		}
		UCF_EventStatics::FireEvent_Template<FM_UEM_SendRawTransactionResponse>(this,FM_UEM_SendRawTransactionResponse(false,StatusCode,Response,"0x"));
	});
	RpcCall->Activate();
}

