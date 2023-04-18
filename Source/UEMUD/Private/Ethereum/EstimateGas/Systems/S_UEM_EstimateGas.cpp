// Fill out your copyright notice in the Description page of Project Settings.


#include "Ethereum/EstimateGas/Systems/S_UEM_EstimateGas.h"

#include "Core/Subsystems/S_CF_Core.h"
#include "Endpoints/RpcCall.h"
#include "Ethereum/EstimateGas/Messages/M_UEM_EstimateGasRequest.h"
#include "Ethereum/EstimateGas/Messages/M_UEM_EstimateGasResponse.h"
#include "Group/StaticFuntionLibrary/CF_GroupsStatics.h"
#include "Group/SubSystems/S_CF_Groups.h"
#include "Hex/FL_UEM_HexConversions.h"
#include "Wallet/Components/Wallet/C_UEM_WalletAddress.h"
#include "Web3Unreal/FL_UEM_Web3EthereumRpcCalls.h"
#include "WorldSettings/Components/C_UEM_WorldSettings.h"
#include "WorldSettings/Systems/S_UEM_LoadWorldSettings.h"

void US_UEM_EstimateGas::Initialize(FSubsystemCollectionBase& Collection)
{


	Collection.InitializeDependency(US_CF_Core::StaticClass());
	Collection.InitializeDependency(US_CF_Groups::StaticClass());
	Collection.InitializeDependency(US_CF_Event::StaticClass());
	Collection.InitializeDependency(US_UEM_LoadWorldSettings::StaticClass());

	
	UCF_EventStatics::AddLambdaListener<FM_UEM_EstimateGasRequest>(this,
		[this](const UObject* Invoker,const FM_UEM_EstimateGasRequest EstimateGasRequest)
	{
		OnEstimateGasRequest(EstimateGasRequest);
	});
	
}

void US_UEM_EstimateGas::OnEstimateGasRequest(FM_UEM_EstimateGasRequest EstimateGasRequest) const
{
	const FC_UEM_WorldSettings worldSettings = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WorldSettings>(this);
	const FC_UEM_WalletAddress wallet = UCF_GroupsStatics::GetSingletonComponent<FC_UEM_WalletAddress>(this);
	URpcCall* RpcCall = UFL_UEM_Web3EthereumRpcCalls::EstimateGasRpcCall(this,wallet.EthWalletAddress,EstimateGasRequest.ToAddress,EstimateGasRequest.EncodedData,FCString::Atoi(*worldSettings.ChainId),"",worldSettings.JsonRPCUrl);
	RpcCall->GetOnCompletedDelegate().AddLambda([this](FString Response,int32 StatusCode)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
		if(FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			if(JsonObject->HasField("result"))
			{
				const FString EstimatedGasHex = JsonObject->GetStringField("result");
				const int32 EstimatedGas = UFL_UEM_HexConversions::GetNumberFromHexString(EstimatedGasHex);
				UCF_EventStatics::FireEvent_Template<FM_UEM_EstimateGasResponse>(this,FM_UEM_EstimateGasResponse(true,StatusCode,Response,EstimatedGas));
			}
			else
			{
				UE_LOG(LogTemp,Error,
				TEXT("No field 'result' in response: %s"),
				*Response);
			}
		}
		UCF_EventStatics::FireEvent_Template<FM_UEM_EstimateGasResponse>(this,FM_UEM_EstimateGasResponse(false,StatusCode,Response,-1));
	});
	RpcCall->Activate();
	
}
