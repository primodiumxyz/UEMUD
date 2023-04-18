// Fill out your copyright notice in the Description page of Project Settings.


#include "Ethereum/GetTransactionCount/Systems/S_UEM_GetTransactionCount.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/RpcCall.h"
#include "Ethereum/GetTransactionCount/Messages/M_UEM_GetTransactionCountRequest.h"
#include "Ethereum/GetTransactionCount/Messages/M_UEM_GetTransactionCountResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Hex/FL_UEM_HexConversions.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"


void US_UEM_GetTransactionCount::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_GetTransactionCountRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_GetTransactionCountRequest GetBalanceRequest)
	{
		OnGetTransactionCountRequest(GetBalanceRequest);
	});
	
}

void US_UEM_GetTransactionCount::OnGetTransactionCountRequest(FM_UEM_GetTransactionCountRequest GetBalanceRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);

	URpcCall* RpcCall = UFL_UEM_Web3EthereumRpcCalls::GetTransactionCountRpcCall(this,wallet.EthWalletAddress,FCString::Atoi(*worldSettings.ChainId),"",worldSettings.JsonRPCUrl);
	RpcCall->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
		if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			if(JsonObject->HasField("result"))
			{
				const FString BalanceHex = JsonObject->GetStringField("result");
				const int32 TransactionCount = UFL_UEM_HexConversions::GetNumberFromHexString(BalanceHex);
				UCF_EventStatics::FireEvent_Template<FM_UEM_GetTransactionCountResponse>(this,FM_UEM_GetTransactionCountResponse(true,StatusCode,Response,TransactionCount));
			}
			else
			{
				UE_LOG(LogTemp,Error,
				TEXT("No field 'result' in response: %s"),
				*Response);
			}
		}
		UCF_EventStatics::FireEvent_Template<FM_UEM_GetTransactionCountResponse>(this,FM_UEM_GetTransactionCountResponse(false,StatusCode,Response,-1));
	});
	RpcCall->Activate();
}

