// Fill out your copyright notice in the Description page of Project Settings.


#include "Ethereum/GetBalance/Systems/S_UEM_GetBalance.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/RpcCall.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceRequest.h"
#include "Ethereum/GetBalance/Messages/M_UEM_GetBalanceResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Hex/FL_UEM_HexConversions.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

void US_UEM_GetBalance::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());
	

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_GetBalanceRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_GetBalanceRequest GetBalanceRequest)
	{
		OnGetBalanceRequest(GetBalanceRequest);
	});
	
}

void US_UEM_GetBalance::OnGetBalanceRequest(FM_UEM_GetBalanceRequest GetBalanceRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	URpcCall* RpcCall = UFL_UEM_Web3EthereumRpcCalls::GetBalanceRpcCall(this,wallet.EthWalletAddress,FCString::Atoi(*worldSettings.ChainId),"",worldSettings.JsonRPCUrl);
	RpcCall->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
		if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			if(JsonObject->HasField("result"))
			{
				const FString BalanceHex = JsonObject->GetStringField("result");
				const int32 Balance = UFL_UEM_HexConversions::GetNumberFromHexString(BalanceHex);
				UCF_EventStatics::FireEvent_Template<FM_UEM_GetBalanceResponse>(this,FM_UEM_GetBalanceResponse(true,StatusCode,Response,Balance));
			}
			else
			{
				UE_LOG(LogTemp,Error,
				TEXT("No field 'result' in response: %s"),
				*Response);
			}
		}
		UCF_EventStatics::FireEvent_Template<FM_UEM_GetBalanceResponse>(this,FM_UEM_GetBalanceResponse(false,StatusCode,Response,-1));
	});
	RpcCall->Activate();
}


